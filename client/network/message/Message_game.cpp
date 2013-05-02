/*
 * Message_game.cpp
 *
 *  Created on: 22 avr. 2013
 *      Author: pierre
 */

#include "Message_game.hpp"
#include "../Network.hpp"

namespace network {

	void Message_game::process(Packet packet) {
		if (packet.getType() == PacketType::GAME_ANSWERREADY) {
			game::GamePlayerList::removeByID(game::CurrentCharacter::get()->getID());
			graphics::Graphics::getWindow()->setContentPane(new graphics::Gameboard());
		}
		else if(packet.getType() == PacketType::GAME_ANSWERMOVE) {
			float x, y;
			packet >> &x >> &y;
			if(game::CurrentCharacter::get()->getCoord() == util::CoordFloat(0,0)) {
				game::CurrentCharacter::get()->setCoord(util::CoordFloat(x,y));
			}
			else
				game::CurrentCharacter::get()->setCoordExtra(util::CoordFloat(x,y));
		}
		else if (packet.getType() == PacketType::GAME_PLAYERMOVE) {
			int id, dir;
			float x, y;
			packet >> &id >> &x >> &y >> &dir;
			game::Player* p = game::GamePlayerList::getByID(id);
			if(p != NULL) {
				p->setCoord(util::CoordFloat(x, y));
				p->setDirection(static_cast<PacketType::PacketContents>(dir));
			}
		}
	}
}


