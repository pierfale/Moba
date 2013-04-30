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
			std::cout << "PACKET RECEIVE" << std::endl;
			graphics::Graphics::getWindow()->setContentPane(new graphics::Gameboard());
		}
	}
}


