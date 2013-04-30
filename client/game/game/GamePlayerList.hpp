/*
 * GamePlayerList.hpp
 *
 *  Created on: 27 avr. 2013
 *      Author: pierre
 */

#ifndef GAMEPLAYERLIST_HPP_
#define GAMEPLAYERLIST_HPP_

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "../character/Player.hpp"

namespace game {

	class GamePlayerList {
	public:
		static bool add(Player* game);
		static Player* get(int i);
		static Player* getByID(int id);
		static void removeByID(int id);
		static int size();

	private:
		GamePlayerList();
		static GamePlayerList* getInstance();
		static boost::shared_ptr<GamePlayerList> m_instance;
		boost::ptr_vector<Player> m_players;
	};
}


#endif /* GAMEPLAYERLIST_HPP_ */
