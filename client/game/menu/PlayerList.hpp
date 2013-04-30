/*
 * PlayerList.hpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#ifndef PLAYERLIST_HPP_
#define PLAYERLIST_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "../character/Player.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace game {

	class PlayerList {

	public:
		static bool add(Player* player);
		static Player* get(int i);
		static int size();
		static void clear();

	private:
		PlayerList();
		static PlayerList* getInstance();
		static boost::shared_ptr<PlayerList> m_instance;
		boost::ptr_vector<Player> m_players;
	};
}


#endif /* PLAYERLIST_HPP_ */
