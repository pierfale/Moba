/*
 * GameList.hpp
 *
 *  Created on: 18 avr. 2013
 *      Author: pierre
 */

#ifndef GAMELIST_HPP_
#define GAMELIST_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "../game/Game.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace game {

	class GameList {

	public:
		static bool add(Game* game);
		static Game* get(int i);
		static Game* getByID(int id);
		static int size();
		static void removeByID(int id);
		static void clear();


	private:
		GameList();
		static GameList* getInstance();
		static boost::shared_ptr<GameList> m_instance;
		boost::ptr_vector<Game> m_games;
	};
}

#endif /* GAMELIST_HPP_ */
