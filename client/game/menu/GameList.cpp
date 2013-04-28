/*
 * GameList.cpp
 *
 *  Created on: 18 avr. 2013
 *      Author: pierre
 */

#include "GameList.hpp"

namespace game {

	boost::shared_ptr<GameList> GameList::m_instance;

	GameList::GameList() {

	}

	bool GameList::add(Game* game) {
		for(int i=0; i<getInstance()->m_games.size(); i++) {
			if(getInstance()->m_games.at(i).getID() == game->getID())
				return false;
		}
		getInstance()->m_games.push_back(game);
		return true;

	}
	Game* GameList::get(int i) {
		return &getInstance()->m_games.at(i);
	}

	int GameList::size() {
		return getInstance()->m_games.size();
	}

	GameList* GameList::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new GameList());
		return m_instance.get();
	}

}


