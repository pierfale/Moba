/*
 * GameList.hpp
 *
 *  Created on: 28 avr. 2013
 *      Author: pierre
 */

#ifndef GAMELIST_HPP_
#define GAMELIST_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "Game.hpp"

class GameList {

public:
	static int size();
	static Game* get(int i);
	static int add(Game* game);
	static void remove(Game* game);
	static Game* getByID(int id);
	static void display();

private:
	GameList();
	static GameList* getInstance();
	static boost::shared_ptr<GameList> m_instance;
	boost::ptr_vector<Game> m_games;
};




#endif /* GAMELIST_HPP_ */
