/*
 * GameCreateList.cpp
 *
 *  Created on: 23 avr. 2013
 *      Author: pierre
 */

#include "GameCreateList.hpp"

boost::shared_ptr<GameCreateList> GameCreateList::m_instance;

GameCreateList::GameCreateList() : m_currID(1) {

}

int GameCreateList::size() {
	return getInstance()->m_games.size();
}

GameCreate* GameCreateList::get(int i) {
	return &getInstance()->m_games.at(i);
}

GameCreate* GameCreateList::getByID(int id) {
	for(unsigned int i=0; i<getInstance()->m_games.size(); i++) {
		if(getInstance()->m_games.at(i).getID() == id)
			return &getInstance()->m_games.at(i);
	}
	return NULL;
}

int GameCreateList::add(GameCreate* game) {
	getInstance()->m_games.push_back(game);
	display();
	return game->getID();
}

void GameCreateList::remove(GameCreate* game) {
	for(boost::ptr_vector<GameCreate>::iterator it = getInstance()->m_games.begin(); it < getInstance()->m_games.end(); ++it) {
		if(game == &(*it)) {
			getInstance()->m_games.release(it).release();
			display();
			return;
		}
	}
}

void GameCreateList::display() {
	log_out "====CreateGame====" end_log_out;
	for(boost::ptr_vector<GameCreate>::iterator it = getInstance()->m_games.begin(); it < getInstance()->m_games.end(); ++it) {
		log_out util::Cast::intToString(it->getID())+"-"+it->getName() end_log_out;
	}
	log_out "==================" end_log_out;
}

int GameCreateList::getNextID() {
	return getInstance()->m_currID++;
}

GameCreateList* GameCreateList::getInstance() {
	if(m_instance.get() == NULL)
		m_instance.reset(new GameCreateList());
	return m_instance.get();
}


