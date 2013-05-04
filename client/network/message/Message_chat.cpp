/*
 * Message_chat.cpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#include "Message_chat.hpp"

namespace network {

	void Message_chat::process(Packet packet) {

		if(packet.getType() == PacketType::CHAT_CREATECHAT) {
			int id, type;
			packet >> &id >> &type;
			if(type == network::PacketType::CHAT_SELECTTEAM) {
				if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::SelectTeamScreen::getName()) {
					((graphics::SelectTeamScreen*)graphics::Graphics::getWindow()->getContentPane())->getChat()->setID(id);
				}
			}
		}
		else if(packet.getType() == PacketType::CHAT_RECEIVEMESSAGE) {
			int id;
			std::string message;
			packet >> &id >> &message;
			graphics::Chat* chat = game::ChatList::getByID(id);
			if(chat != NULL) {
				chat->receive(message);
			}
		}

	}
}


