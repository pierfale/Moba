/*
 * Message_session.cpp
 *
 *  Created on: 22 avr. 2013
 *      Author: pierre
 */

#include "Message_session.hpp"
#include "../Network.hpp"

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
		}
		else if(packet.getType() == PacketType::SESSION_ANSWERCHARACTER) {
			std::cout << "beg!" << std::endl;
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
	}
}


