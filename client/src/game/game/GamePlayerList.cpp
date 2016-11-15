/*
 * GamePlayerList.cpp
 *
 *  Created on: 27 avr. 2013
 *      Author: pierre
 */

#include "GamePlayerList.hpp"

namespace game {

	boost::shared_ptr<GamePlayerList> GamePlayerList::m_instance;

	GamePlayerList::GamePlayerList() {

	}

	bool GamePlayerList::add(Player* player) {
		for(unsigned int i=0; i<getInstance()->m_players.size(); i++) {
			if(getInstance()->m_players.at(i).getID() == player->getID())
				return false;
		}
		getInstance()->m_players.push_back(player);
		return true;

	}
	Player* GamePlayerList::get(int i) {
		return &getInstance()->m_players.at(i);
	}

	Player* GamePlayerList::getByID(int id) {
		for(unsigned int i=0; i<getInstance()->m_players.size(); i++) {
			if(getInstance()->m_players.at(i).getID() == id)
				return &getInstance()->m_players.at(i);
		}
		return NULL;
	}

	void GamePlayerList::removeByID(int id) {
		for(boost::ptr_vector<Player>::iterator it = getInstance()->m_players.begin(); it < getInstance()->m_players.end(); ++it) {
			if(it->getID() == id) {
				getInstance()->m_players.release(it);
				return;
			}
		}
	}

	void GamePlayerList::clear() {
		getInstance()->m_players.clear();
	}
	int GamePlayerList::size() {
		return getInstance()->m_players.size();
	}

	GamePlayerList* GamePlayerList::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new GamePlayerList());
		return m_instance.get();
	}

}



