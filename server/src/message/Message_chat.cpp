/*
 * Message_chat.cpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#include "Message_chat.hpp"

namespace network {

	void Message_chat::process(Packet packet, Client* client) {

		if(packet.getType() == PacketType::CHAT_SENDMESSAGE) {
			int id;
			std::string message;
			packet >> &id >> &message;
			Chat* chat = ChatList::getByID(id);
			if(chat != NULL) {
				if(chat->isClient(client)) {
					message = "["+client->getCharacter()->getName()+"] "+message;
					Packet answer(NULL, PacketType::CHAT_RECEIVEMESSAGE);
					answer << id << "<color=240,255,255><size=16>"+message+"</size></color>";
					chat->sendAll(answer);
				}
			}
		}
	}
}


