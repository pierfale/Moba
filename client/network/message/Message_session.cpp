/*
 * Message_session.cpp
 *
 *  Created on: 22 avr. 2013
 *      Author: pierre
 */

#include "Message_session.hpp"
#include "../Network.hpp"
#include "../../graphics/screen/ScreenManager.hpp"

namespace network {

	void Message_session::process(Packet packet) {

		if(packet.getType() == PacketType::SESSION_ANSWERCONNECTION) {
			int contents;
			packet >> &contents;
			if(contents == PacketType::LOGIN_OK) {
				if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::ConnectionScreen::getName()) {
					((graphics::ConnectionScreen*)graphics::Graphics::getWindow()->getContentPane())->setMessage("Connected!");
					((graphics::ConnectionScreen*)graphics::Graphics::getWindow()->getContentPane())->setConnected();
				}
			}
			else if(contents == PacketType::NONEXISTENT_ACCOUNT) {
				if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::ConnectionScreen::getName())
					((graphics::ConnectionScreen*)graphics::Graphics::getWindow()->getContentPane())->setMessage("Non-existent account");
				Network::close();
			}
			else if(contents == PacketType::BAD_PASSWORD) {
				if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::ConnectionScreen::getName())
					((graphics::ConnectionScreen*)graphics::Graphics::getWindow()->getContentPane())->setMessage("Bad password!");
				Network::close();
			}
			else if(contents == PacketType::ALREADY_LOGGED) {
				if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::ConnectionScreen::getName())
					((graphics::ConnectionScreen*)graphics::Graphics::getWindow()->getContentPane())->setMessage("Already logged in!");
				Network::close();
			}
		}
		else if(packet.getType() == PacketType::SESSION_ANSWERCHARACTER) {
			std::string name;
			int id, level, exp;
			packet >> &id >> &name >> &level >> &exp;
			if(game::PlayerList::add(new game::Player(id, name, level, exp))) {
				if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::CharacterScreen::getName())
					((graphics::CharacterScreen*)graphics::Graphics::getWindow()->getContentPane())->refreshCharacter();
			}
		}
		else if(packet.getType() == PacketType::SESSION_ANSWERGAME) {
			std::string name, creator;
			int id, nPlayer;
			packet >> &id >> &name >> &creator >> &nPlayer;

			if(game::GameList::add(new game::Game(id, name, creator, nPlayer))) {
				if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::GameListScreen::getName())
					((graphics::GameListScreen*)graphics::Graphics::getWindow()->getContentPane())->refreshGame();
			}
		}
		else if(packet.getType() == PacketType::SESSION_ANSWERJOINGAME) {
			int id;
			packet >> &id;
			game::Game* game = game::GameList::getByID(id);
			if(game != NULL) {
				graphics::Graphics::getWindow()->setContentPane(graphics::ScreenManager::selectTeam(game));
			}
		}
		else if(packet.getType() == PacketType::SESSION_PLAYERJOINGAME) {
				int id, level, team, exp;
				std::string name;
				packet >> &id >> &name >> &level >> &exp >>&team;
				game::Player* player = NULL;
				if (id == game::CurrentCharacter::get()->getID()) {
					player = game::CurrentCharacter::get();
					player->setFaction(static_cast<PacketType::PacketContents>(team));
				}
				player = new game::Player(id , name, level, exp);
				player->setFaction(static_cast<PacketType::PacketContents>(team));
				std::cout << "--->" << id << ":" << name << ":" << level << ":" << exp << ":" << team << std::endl;
				game::GamePlayerList::add(player);
				if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::SelectTeamScreen::getName())
					((graphics::SelectTeamScreen*)graphics::Graphics::getWindow()->getContentPane())->refreshPlayer();
			}
		else if(packet.getType() == PacketType::SESSION_PLAYERCHANGETEAM) {
			int id, team;
			packet >> &id >> &team;
			game::Player* p = NULL;
			if (id == game::CurrentCharacter::get()->getID()) {
				p = game::CurrentCharacter::get();
				p->setFaction(static_cast<PacketType::PacketContents>(team));
			}
			p = game::GamePlayerList::getByID(id);
			if(p != NULL) {
				p->setFaction(static_cast<PacketType::PacketContents>(team));
				if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::SelectTeamScreen::getName()) {
					((graphics::SelectTeamScreen*)graphics::Graphics::getWindow()->getContentPane())->refreshPlayer();
				}
			}
		}
		else if(packet.getType() == PacketType::SESSION_PLAYERQUITGAME) {
			int id;
			packet >> &id;
			game::GamePlayerList::removeByID(id);
			if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::SelectTeamScreen::getName()) {
				((graphics::SelectTeamScreen*)graphics::Graphics::getWindow()->getContentPane())->refreshPlayer();
			}
		}
		else if(packet.getType() == PacketType::SESSION_GAMEDELETE) {
			int id;
			packet >> &id;
			if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::SelectTeamScreen::getName()) {
				if(((graphics::SelectTeamScreen*)graphics::Graphics::getWindow()->getContentPane())->getGame()->getID() == id) {
					game::GamePlayerList::clear();
					game::GameList::removeByID(id);
					graphics::Graphics::getWindow()->setContentPane(graphics::ScreenManager::gameList());
				}
				else
					game::GameList::removeByID(id);
			}
			else if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::GameListScreen::getName()) {
				game::GameList::removeByID(id);
				((graphics::GameListScreen*)graphics::Graphics::getWindow()->getContentPane())->refreshGame();
			}

		}
		else if(packet.getType() == PacketType::SESSION_NPLAYERGAME) {
			int id, number;
			packet >> &id >> &number;
			game::GameList::getByID(id)->setNPlayer(number);
			 if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::GameListScreen::getName())
				 ((graphics::GameListScreen*)graphics::Graphics::getWindow()->getContentPane())->refreshGame();
		}
		else if (packet.getType() == PacketType::SESSION_ANSWERLAUNCHGAME) {
			game::CurrentCharacter::get(); // TODO path of file to load
			graphics::Gameboard::loadImage();
			network::Packet ready_packet(network::Network::getSocket(), network::PacketType::GAME_ASKREADY);
			ready_packet.send();
		}
		else if (packet.getType() == PacketType::SESSION_ANSWERSKILL) {
			if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::CharacterScreen::getName()) {
				if(((graphics::CharacterScreen*)graphics::Graphics::getWindow()->getContentPane())->getMainFrame()->getComponentName() == graphics::CharacterSkill::getName()) {
					int id;
					packet >> &id;
					((graphics::CharacterSkill*)((graphics::CharacterScreen*)graphics::Graphics::getWindow()->getContentPane())->getMainFrame())->setActiveSkill(id);
				}
			}
		}
		else if (packet.getType() == PacketType::SESSION_ANSWERALLSKILL) {
			if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::CharacterScreen::getName()) {
				if(((graphics::CharacterScreen*)graphics::Graphics::getWindow()->getContentPane())->getMainFrame()->getComponentName() == graphics::CharacterSkill::getName()) {
					int size;
					packet >> &size;
					for(int i=0; i<size; i++) {
						int id;
						packet >> &id;
						((graphics::CharacterSkill*)((graphics::CharacterScreen*)graphics::Graphics::getWindow()->getContentPane())->getMainFrame())->setActiveSkill(id);
					}
				}
			}
		}
		else if(packet.getType() == PacketType::SESSION_ANSWERALLSTAT) {
					int life;
					int maxLife;
					int mana;
					int maxMana;
					float attackSpeed;
					float movementSpeed;
					int physicalAttack;
					int magicalAttack;
					int physicalArmor;
					int magicalArmor;
					float range;

					packet >> &life >> &maxLife >> &mana >> &maxMana >> &attackSpeed >> &movementSpeed >> &physicalAttack >> &magicalAttack >> &physicalArmor >> &magicalArmor >> &range;
					if(game::CurrentCharacter::get() != NULL) {
						game::CurrentCharacter::get()->getStat()->setLife(life);
						game::CurrentCharacter::get()->getStat()->setMaxLife(maxLife);
						game::CurrentCharacter::get()->getStat()->setMana(mana);
						game::CurrentCharacter::get()->getStat()->setMaxMana(maxMana);
						game::CurrentCharacter::get()->getStat()->setAttackSpeed(attackSpeed);
						game::CurrentCharacter::get()->getStat()->setMovementSpeed(movementSpeed);
						game::CurrentCharacter::get()->getStat()->setPhysicalAttack(physicalAttack);
						game::CurrentCharacter::get()->getStat()->setMagicalAttack(magicalAttack);
						game::CurrentCharacter::get()->getStat()->setPhysicalArmor(physicalArmor);
						game::CurrentCharacter::get()->getStat()->setMagicalArmor(magicalArmor);
						game::CurrentCharacter::get()->getStat()->setRange(range);
						if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::CharacterScreen::getName()) {
							if(((graphics::CharacterScreen*)graphics::Graphics::getWindow()->getContentPane())->getMainFrame()->getComponentName() == graphics::CharacterInfo::getName()) {
								((graphics::CharacterInfo*)((graphics::CharacterScreen*)graphics::Graphics::getWindow()->getContentPane())->getMainFrame())->refresh();
							}
						}
					}
				}
	}
}


