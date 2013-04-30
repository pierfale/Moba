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
			int id;
			packet >> &id >> &name >> &creator;
			if(game::GameList::add(new game::Game(id, name, creator))) {
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
		else if (packet.getType() == PacketType::SESSION_ANSWERLAUNCHGAME) {
			game::GameboardModel::setClientPlayer(game::CurrentCharacter::get()); // TODO path of file to load
			for (int i = 0 ; i < game::GamePlayerList::size() ; i++) {game::GameboardModel::addPlayer(game::GamePlayerList::get(i));}
			graphics::Gameboard::loadImage();
			network::Packet ready_packet(network::Network::getSocket(), network::PacketType::GAME_ASKREADY);
			ready_packet.send();
			std::cout << "PACKET SEND!" << std::endl;
		}
		else if (packet.getType() == PacketType::GAME_ANSWERREADY) {
			std::cout << "PACKET RECEIVE" << std::endl;
			graphics::Graphics::getWindow()->setContentPane(new graphics::Gameboard());
		}
	}
}


