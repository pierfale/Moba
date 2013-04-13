/*
 * PlayerList.hpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#ifndef PLAYERLIST_HPP_
#define PLAYERLIST_HPP_

#include "../character/Player.hpp"
#include <boost/ptr_container/ptr_vector.hpp>

namespace game {

	class PlayerList {

	public:
		static void add(Player* player);
		static Player* get(int i);
		static int size();

	private:
		PlayerList();
		static PlayerList* getInstance();
		static PlayerList* m_instance;
		boost::ptr_vector<Player> m_players;
	};
}


#endif /* PLAYERLIST_HPP_ */
