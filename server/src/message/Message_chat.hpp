/*
 * Message_chat.hpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#ifndef MESSAGE_CHAT_HPP_
#define MESSAGE_CHAT_HPP_

#include "Packet.hpp"
#include "../client/Client.hpp"
#include "../chat/Chat.hpp"
#include "../chat/ChatList.hpp"

namespace network {

	class Message_chat {

	public:
		static void process(Packet packet, Client* client);
	};

}


#endif /* MESSAGE_CHAT_HPP_ */
