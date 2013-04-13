/*
 * PlayerList.cpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#include "PlayerList.hpp"

namespace game {

	PlayerList* PlayerList::m_instance = NULL;

	PlayerList::PlayerList() {
		//tmp
		m_players.push_back(new Player(1, "pierfale", 100));
		m_players.push_back(new Player(2, "béni", 50));
	}

	void PlayerList::add(Player* player) {
		getInstance()->m_players.push_back(player);

	}
	Player* PlayerList::get(int i) {
		return &getInstance()->m_players.at(i);
	}

	int PlayerList::size() {
		return getInstance()->m_players.size();
	}

	PlayerList* PlayerList::getInstance() {
		if(m_instance == NULL)
			m_instance = new PlayerList();
		return m_instance;
	}

}


