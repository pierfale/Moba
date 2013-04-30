/*
 * CurrentCharacter.cpp
 *
 *  Created on: 23 avr. 2013
 *      Author: pierre
 */

#include "CurrentCharacter.hpp"

namespace game {

	boost::shared_ptr<CurrentCharacter> CurrentCharacter::m_instance;

	CurrentCharacter::CurrentCharacter() : m_current(NULL) {

	}

	Player* CurrentCharacter::get() {
		return getInstance()->m_current;
	}

	void CurrentCharacter::set(Player* player) {
		if(getInstance()->m_current != player) {
			network::Packet packet(network::Network::getSocket(), network::PacketType::SESSION_SELECTCHARACTER);
			packet << player->getID();
			packet.send();
		}
		getInstance()->m_current = player;
	}

	void CurrentCharacter::reset() {
		getInstance()->m_current = NULL;
	}

	CurrentCharacter* CurrentCharacter::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new CurrentCharacter());
		return m_instance.get();
	}

}


