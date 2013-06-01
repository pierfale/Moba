/*
 * Player.hpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#ifndef GAME_PLAYER_HPP_
#define GAME_PLAYER_HPP_

#include "Character.hpp"
#include "PlayerStat.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"


namespace game {

	class Player : public Character {

	public:
		Player(int id, std::string name, int level);
		PlayerStat* getStat();
		int getLevel();
		int getDie();
		int getFrag();

		void incDie();
		void incFrag();


	private:
		int m_level, m_nb_die, m_nb_frag;
	};
}


#endif /* PLAYER_HPP_ */
