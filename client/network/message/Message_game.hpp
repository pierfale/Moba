/*
 * Message_session.hpp
 *
 *  Created on: 22 avr. 2013
 *      Author: pierre
 */

#ifndef MESSAGE_GAME_HPP_
#define MESSAGE_GAME_HPP_

#include <boost/thread/thread.hpp>
#include "Packet.hpp"
#include "PacketType.hpp"
#include "../../graphics/Graphics.hpp"
#include "../../graphics/game/Gameboard.h"
#include "../../graphics/game/animation/spell/SingleTargetSpellImpl.hpp"

#include "../../game/character/Player.hpp"
#include "../../game/menu/PlayerList.hpp"
#include "../../game/game/Game.hpp"
#include "../../game/game/GameboardModel.h"
#include "../../game/game/GamePlayerList.hpp"
#include "../../game/menu/GameList.hpp"

namespace network {

	class Message_game {
	public:
		static void process(Packet packet);
	};

}


#endif /* MESSAGE_GAME_HPP_ */
