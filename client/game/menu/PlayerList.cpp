/*
 * PlayerList.cpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#include "PlayerList.hpp"

namespace game {

	boost::shared_ptr<PlayerList> PlayerList::m_instance;

	PlayerList::PlayerList() {

	}

	bool PlayerList::add(Player* player) {
		for(unsigned int i=0; i<getInstance()->m_players.size(); i++) {
			if(getInstance()->m_players.at(i).getID() == player->getID())
				return false;
		}
		getInstance()->m_players.push_back(player);
		return true;
	}
	Player* PlayerList::get(int i) {
		return &getInstance()->m_players.at(i);
	}

	int PlayerList::size() {
		return getInstance()->m_players.size();
	}

	void PlayerList::clear() {
		getInstance()->m_players.clear();
	}

	PlayerList* PlayerList::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new PlayerList());
		return m_instance.get();
	}

}


