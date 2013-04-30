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
			int id, level;
			packet >> &id >> &name >> &level;
			if(game::PlayerList::add(new game::Player(id, name, level))) {
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
			int id, level, team;
			std::string name;
			packet >> &id >> &name >> &level >> &team;
			game::Player* player = new game::Player(id , name, level);
			player->setTeam(team);
			std::cout << "--->" << id << ":" << name << ":" << level << ":" << team << std::endl;
			game::GamePlayerList::add(player);
			if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::SelectTeamScreen::getName())
				((graphics::SelectTeamScreen*)graphics::Graphics::getWindow()->getContentPane())->refreshPlayer();
		}
		else if(packet.getType() == PacketType::SESSION_PLAYERCHANGETEAM) {
			int id, team;
			packet >> &id >> &team;
			game::GamePlayerList::getByID(id)->setTeam(team);
			if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::SelectTeamScreen::getName()) {
				((graphics::SelectTeamScreen*)graphics::Graphics::getWindow()->getContentPane())->refreshPlayer();
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
	}
}

