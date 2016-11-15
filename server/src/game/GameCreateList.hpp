/*
 * GameCreateList.hpp
 *
 *  Created on: 23 avr. 2013
 *      Author: pierre
 */

#ifndef GAMECREATELIST_HPP_
#define GAMECREATELIST_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "GameCreate.hpp"

class GameCreateList {

public:
	static int size();
	static GameCreate* get(int i);
	static int add(GameCreate* game);
	static void remove(GameCreate* game);
	static int getNextID();
	static GameCreate* getByID(int id);
	static void display();

private:
	GameCreateList();
	static GameCreateList* getInstance();
	static boost::shared_ptr<GameCreateList> m_instance;
	boost::ptr_vector<GameCreate> m_games;
	int m_currID;
};


#endif /* GAMECREATELIST_HPP_ */
