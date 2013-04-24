/*
 * Message_session.hpp
 *
 *  Created on: 22 avr. 2013
 *      Author: pierre
 */

#ifndef MESSAGE_SESSION_HPP_
#define MESSAGE_SESSION_HPP_

#include <boost/thread/thread.hpp>
#include "Packet.hpp"
#include "PacketType.hpp"
#include "../../graphics/Graphics.hpp"
#include "../../graphics/screen/ConnectionScreen.hpp"
#include "../../graphics/screen/CharacterScreen.hpp"
#include "../../graphics/screen/GameListScreen.hpp"

#include "../../game/character/Player.hpp"
#include "../../game/menu/PlayerList.hpp"
#include "../../game/game/Game.hpp"
#include "../../game/menu/GameList.hpp"

namespace network {

	class Message_session {

	public:
		static void process(Packet packet);
	};

}


#endif /* MESSAGE_SESSION_HPP_ */
