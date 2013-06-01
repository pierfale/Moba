/*
 * CurrentCharacter.cpp
 *
 *  Created on: 23 avr. 2013
 *      Author: pierre
 */

#include "CurrentCharacter.hpp"

namespace game {

	boost::shared_ptr<CurrentCharacter> CurrentCharacter::m_instance;

	CurrentCharacter::CurrentCharacter() : m_current(NULL), m_currentView(NULL), m_target(NULL) {

	}

	Player* CurrentCharacter::get() {
		return getInstance()->m_current;
	}

	graphics::UserPlayer* CurrentCharacter::getView() {
		return getInstance()->m_currentView;
	}

	Character* CurrentCharacter::getTarget() {
		return getInstance()->m_target;
	}

	void CurrentCharacter::set(Player* player) {
		if(getInstance()->m_current != player) {
			network::Packet packet(network::Network::getSocket(), network::PacketType::SESSION_SELECTCHARACTER);
			packet << player->getID();
			packet.send();
		}
		getInstance()->m_current = player;
	}


	void CurrentCharacter::set(graphics::UserPlayer* player) {
		getInstance()->m_currentView = player;
	}

	void CurrentCharacter::setTarget(Character* player) {
		getInstance()->m_target = player;
		if(player == NULL)
			log_out "[Target] No target" end_log_out;
		else
			log_out "[Target] "+player->getName() end_log_out;
	}

	void CurrentCharacter::setPath(std::vector<util::CoordInt> path) {
		getInstance()->m_path = path;
	}

	util::CoordInt CurrentCharacter::getNextDest() {
		if(getInstance()->m_path.size() > 0)
			return getInstance()->m_path.at(getInstance()->m_path.size()-1);
		else
			return util::CoordInt(-1,-1);
	}

	void CurrentCharacter::destReached() {
		if(getInstance()->m_path.size() > 0)
			getInstance()->m_path.erase(getInstance()->m_path.begin()+getInstance()->m_path.size()-1);
	}

	bool CurrentCharacter::isLastDest() {
		return getInstance()->m_path.size() == 1;
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


