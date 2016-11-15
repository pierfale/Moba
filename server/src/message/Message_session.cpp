/*
 * Message_session.cpp
 *
 *  Created on: 21 avr. 2013
 *      Author: pierre
 */

#include "Message_session.hpp"

namespace network {

	void Message_session::process(Packet packet, Client* client) {
		if(packet.getType() == PacketType::SESSION_ASKCONNECTION) {
			Packet answer(client->getSocket(), PacketType::SESSION_ANSWERCONNECTION);
			std::string pseudo, password;
			packet >> &pseudo >> &password;
			ResultQuery* result = Database::query("SELECT Account_ID, Account_Password FROM account WHERE Account_Pseudo = '"+pseudo+"'");
			if(result->next()) {
				if(result->get("Account_Password") == password) {
					if(Server::getClientByID(util::Cast::stringToInt(result->get("Account_ID"))) == NULL) {
						answer << PacketType::LOGIN_OK;
						client->setAccount(util::Cast::stringToInt(result->get("Account_ID")), pseudo);
					}
					else
						answer << PacketType::ALREADY_LOGGED;
				}
				else {
					answer << PacketType::BAD_PASSWORD;
				}
			}
			else {
				answer << PacketType::NONEXISTENT_ACCOUNT;
			}
			result->free();
			answer.send();

		}
		else if(packet.getType() == PacketType::SESSION_ASKCHARACTER) {
			ResultQuery* result = Database::query("SELECT Characters_ID, Characters_Name, Characters_Level FROM characters WHERE Characters_Account = '"+util::Cast::intToString(client->getAccountID())+"'");
			while(result->next()) {
				std::cout << "--> " << result->get("Characters_Name") << std::endl;
				Packet answer(client->getSocket(), PacketType::SESSION_ANSWERCHARACTER);
				answer << util::Cast::stringToInt(result->get("Characters_ID")) << result->get("Characters_Name") <<  util::Cast::stringToInt(result->get("Characters_Level")) << 0; //TODO GET CURREXP FROM DB
				answer.send();
			}
			result->free();
		}
		else if(packet.getType() == PacketType::SESSION_ASKGAME) {
			for(int i=0; i<GameCreateList::size(); i++) {
				Packet answer(client->getSocket(), PacketType::SESSION_ANSWERGAME);
				answer << GameCreateList::get(i)->getID() << GameCreateList::get(i)->getName() << GameCreateList::get(i)->getCreator()->getCharacter()->getName() << GameCreateList::get(i)->playerSize();
				answer.send();
			}
		}
		else if(packet.getType() == PacketType::SESSION_SELECTCHARACTER) {
			int id;
			packet >> &id;
			if(id == 0) {
				client->setCharacter(NULL);
			}
			else {
				bool ok = false;
				ResultQuery* result = Database::query("SELECT Characters_Account, Characters_Name, Characters_Level, Characters_Exp FROM characters WHERE Characters_ID = '"+util::Cast::intToString(id)+"'");
				if(result->next()) {
					if(util::Cast::stringToInt(result->get("Characters_Account")) == client->getAccountID()) {
						client->setCharacter(new Player(id, client, result->get("Characters_Name"), util::Cast::stringToInt(result->get("Characters_Level")),  util::Cast::stringToInt(result->get("Characters_Exp"))));
						ok = true;
					}
				}
				result->free();

				if(ok) {
					ResultQuery* result = Database::query("SELECT Skill_ID FROM skill WHERE Skill_Characters = '"+util::Cast::intToString(id)+"'");
					while(result->next()) {
						Skill* s = SkillReader::get(util::Cast::stringToInt(result->get("Skill_ID")));
						if(s != NULL)
							client->getCharacter()->addSkill(s);

					}
					result->free();
				}
			}
			//TODO else disconnect
		}
		else if(packet.getType() == PacketType::SESSION_CLOSE) {
			client->close();
			client->stop();
		}
		else if(packet.getType() == PacketType::SESSION_CREATECHARACTER) {
			//TODO check the name is good
			std::string name;
			packet >> &name;
			Database::update("INSERT INTO characters(Characters_Account, Characters_Name, Characters_Level, Characters_Exp)"
							"VALUES('"+util::Cast::intToString(client->getAccountID())+"', '"+name+"', '1', '0')");
			int id = Database::lastInsertID();
			Packet answer(client->getSocket(), PacketType::SESSION_ANSWERCHARACTER);
			answer << id << name <<  1 << 0; //LVL 1 EXP 0
			answer.send();
		}
		else if(packet.getType() == PacketType::SESSION_CREATEGAME) {
			std::string name;
			packet >> &name;
			GameCreate* game = new GameCreate(name, client);
			int id = game->getID();
			GameCreateList::add(game);
			client->setGameCreate(game);
			Packet answer(client->getSocket(), PacketType::SESSION_ANSWERGAME);
			answer << id << game->getName() << client->getCharacter()->getName() << 1;
			//TODO create list
			Server::sendAll(answer);

			Packet answer2(client->getSocket(), PacketType::SESSION_ANSWERJOINGAME);
			answer2 << id;
			answer2.send();

			client->getCharacter()->setTeam(PacketType::FACTION_TEAM1);

			Packet answer3(client->getSocket(), PacketType::SESSION_PLAYERJOINGAME);
			answer3 << client->getCharacter()->getID() << client->getCharacter()->getName() << client->getCharacter()->getLevel() << client->getCharacter()->getExp() <<client->getCharacter()->getTeam();
			answer3.send();

			game->getChat()->addClient(client);
		}
		else if(packet.getType() == PacketType::SESSION_ASKJOINGAME) {
			int id;
			packet >> &id;
			GameCreate* game = GameCreateList::getByID(id);
			if(game != NULL) {
				client->setGameCreate(game);
				client->getCharacter()->setTeam(PacketType::FACTION_TEAM1);
				Packet answer(client->getSocket(), PacketType::SESSION_ANSWERJOINGAME);
				answer << id;
				answer.send();

				for(int i=0; i<game->playerSize(); i++) {
					Packet answer2(client->getSocket(), PacketType::SESSION_PLAYERJOINGAME);
					answer2 << game->getPlayer(i)->getCharacter()->getID() << game->getPlayer(i)->getCharacter()->getName() << game->getPlayer(i)->getCharacter()->getLevel() << game->getPlayer(i)->getCharacter()->getExp() << game->getPlayer(i)->getCharacter()->getTeam();
					answer2.send();
				}

				Packet answer2(client->getSocket(), PacketType::SESSION_PLAYERJOINGAME);
				answer2 << client->getCharacter()->getID() << client->getCharacter()->getName() << client->getCharacter()->getLevel() << client->getCharacter()->getExp() << client->getCharacter()->getTeam();
				game->sendAll(answer2);

				Packet answer3(client->getSocket(), PacketType::SESSION_NPLAYERGAME);
				answer3 << game->getID() << game->playerSize();
				//TODO change to list...
				Server::sendAll(answer3);

				game->getChat()->addClient(client);

			}
		}
		else if(packet.getType() == PacketType::SESSION_ASKCHANGETEAM) {
			if(client->getCharacter()->getTeam() == PacketType::FACTION_TEAM1)
				client->getCharacter()->setTeam(PacketType::FACTION_TEAM2);
			else
				client->getCharacter()->setTeam(PacketType::FACTION_TEAM1);

			Packet answer(client->getSocket(), PacketType::SESSION_PLAYERCHANGETEAM);
			answer << client->getCharacter()->getID() << client->getCharacter()->getTeam();
			client->getGameCreate()->sendAll(answer);
		}
		else if(packet.getType() == PacketType::SESSION_ASKQUITGAME) {
			if(client->getGameCreate()->removePlayer(client)) {
				Packet answer(client->getSocket(), PacketType::SESSION_GAMEDELETE);
				answer << client->getGameCreate()->getID();
				//TODO create list
				Server::sendAll(answer);
				GameCreateList::remove(client->getGameCreate());
				delete client->getGameCreate();
			}
			else {
				Packet answer(client->getSocket(), PacketType::SESSION_PLAYERQUITGAME);
				answer << client->getCharacter()->getID();
				client->getGameCreate()->sendAll(answer);

				Packet answer2(client->getSocket(), PacketType::SESSION_NPLAYERGAME);
				answer2 << client->getGameCreate()->getID() << client->getGameCreate()->playerSize();
				//TODO change to list...
				Server::sendAll(answer2);
			}
			client->setGameCreate(NULL);
		}
		else if(packet.getType() == PacketType::SESSION_ASKLAUNCHGAME) {
			if(client->getGameCreate()->getCreator() == client) {
				Game* game = new Game(new Pvp(), client->getGameCreate());

				GameList::add(game);
				boost::thread(boost::bind(&Game::run, game));
				Packet answer(client->getSocket(), PacketType::SESSION_ANSWERLAUNCHGAME);
				game->sendAll(answer);
			}
		}
		else if(packet.getType() == PacketType::SESSION_ASKSKILL) {
			int id;
			packet >> &id;
			Skill* s = SkillReader::get(id);

			if(s != NULL) {
				bool ok = false;
				if(s->parentSize() == 0)
					ok = true;
				for(int i=0; !ok && i<client->getCharacter()->skillSize(); i++) {
					for(int j=0; j<s->parentSize(); j++) {
						if(s->getParent(j) == client->getCharacter()->getSkill(i)->getId())
							ok = true;
					}
				}

				for(int i=0; ok && i<client->getCharacter()->skillSize(); i++) {
					if(client->getCharacter()->getSkill(i)->getId() == id)
						ok = false;
				}
				if(ok && client->getCharacter()->getLevel() > client->getCharacter()->skillSize()) {
					Packet answer(client->getSocket(), PacketType::SESSION_ANSWERSKILL);
					answer << id;
					answer.send();
					client->getCharacter()->addSkill(s);
					Database::update("INSERT INTO skill(Skill_ID, Skill_Characters)"
												"VALUES('"+util::Cast::intToString(id)+"', '"+util::Cast::intToString(client->getCharacter()->getID())+"')");
				}
			}
		}
		else if(packet.getType() == PacketType::SESSION_ASKALLSKILL) {
			Packet answer(client->getSocket(), PacketType::SESSION_ANSWERALLSKILL);
			answer << client->getCharacter()->skillSize();
			for(int i=0; i<client->getCharacter()->skillSize(); i++) {
				answer << client->getCharacter()->getSkill(i)->getId();
			}
			answer.send();
		}
		else if(packet.getType() == PacketType::SESSION_ASKALLSTAT) {
			network::Packet answer(client->getSocket(), network::PacketType::SESSION_ANSWERALLSTAT);
			if(client->getCharacter() != NULL) {
				client->getCharacter()->updateStat();
				answer << client->getCharacter()->getStat()->life();
				answer << client->getCharacter()->getStat()->maxLife();
				answer << client->getCharacter()->getStat()->mana();
				answer << client->getCharacter()->getStat()->maxMana();
				answer << client->getCharacter()->getStat()->attackSpeed();
				answer << client->getCharacter()->getStat()->movementSpeed();
				answer << client->getCharacter()->getStat()->physicalAttack();
				answer << client->getCharacter()->getStat()->magicalAttack();
				answer << client->getCharacter()->getStat()->physicalArmor();
				answer << client->getCharacter()->getStat()->magicalArmor();
				answer << client->getCharacter()->getStat()->range();
				answer.send();
			}
		}

	}

}

