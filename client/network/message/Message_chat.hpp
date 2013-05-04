/*
 * Message_Chat.hpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#ifndef MESSAGE_CHAT_HPP_
#define MESSAGE_CHAT_HPP_

#include <string>
#include "Packet.hpp"
#include "../../graphics/Graphics.hpp"
#include "../../graphics/screen/SelectTeamScreen.hpp"


namespace network {

	class Message_chat {

	public:
		static void process(Packet packet);

	};

}



#endif /* MESSAGE_CHAT_HPP_ */
