/*
 * Message_session.hpp
 *
 *  Created on: 21 avr. 2013
 *      Author: pierre
 */

#ifndef MESSAGE_SESSION_HPP_
#define MESSAGE_SESSION_HPP_

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "Packet.hpp"
#include "../client/Client.hpp"
#include "../database/Database.hpp"
#include "../database/ResultQuery.hpp"
#include "../game/Game.hpp"
#include "../game/GameCreateList.hpp"
#include "../game/GameList.hpp"
#include "../game/mode/Pvp.hpp"
#include "../network/Server.hpp"
#include "../skill/SkillReader.hpp"

namespace network {

	class Message_session {

	public:
		static void process(network::Packet packet, Client* client);
	};

}

#endif /* MESSAGE_SESSION_HPP_ */
