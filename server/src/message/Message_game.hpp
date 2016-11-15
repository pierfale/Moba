/*
 * Message_game.hpp
 *
 *  Created on: 28 avr. 2013
 *      Author: pierre
 */

#ifndef MESSAGE_GAME_HPP_
#define MESSAGE_GAME_HPP_

#include "Packet.hpp"
#include "../client/Client.hpp"
#include "../game/Game.hpp"
#include "../spell/SingleTargetSpell.hpp"

namespace network {

	class Message_game {

	public:
		static void process(Packet packet, Client* client);
	};

}



#endif /* MESSAGE_GAME_HPP_ */
