/*
 * GameList.cpp
 *
 *  Created on: 28 avr. 2013
 *      Author: pierre
 */

#include "GameList.hpp"

boost::shared_ptr<GameList> GameList::m_instance;

GameList::GameList() {

}

int GameList::size() {
	return getInstance()->m_games.size();
}

Game* GameList::get(int i) {
	return &getInstance()->m_games.at(i);
}

Game* GameList::getByID(int id) {
	for(unsigned int i=0; i<getInstance()->m_games.size(); i++) {
		if(getInstance()->m_games.at(i).getID() == id)
			return &getInstance()->m_games.at(i);
	}
	return NULL;
}

int GameList::add(Game* game) {
	getInstance()->m_games.push_back(game);
	display();
	return game->getID();
}

void GameList::remove(Game* game) {
	for(boost::ptr_vector<Game>::iterator it = getInstance()->m_games.begin(); it < getInstance()->m_games.end(); ++it) {
		if(game == &(*it)) {
			getInstance()->m_games.release(it).release();
			display();
			return;
		}
	}
}

void GameList::display() {
	log_out "=======Game=======" end_log_out;
	for(boost::ptr_vector<Game>::iterator it = getInstance()->m_games.begin(); it < getInstance()->m_games.end(); ++it) {
		log_out util::Cast::intToString(it->getID()) end_log_out;
	}
	log_out "==================" end_log_out;
}

GameList* GameList::getInstance() {
	if(m_instance.get() == NULL)
		m_instance.reset(new GameList());
	return m_instance.get();
}

