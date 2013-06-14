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
		Player(int id, std::string name, int level, int exp);

		PlayerStat* getStat();
		int getLevel();
		int getDie();
		int getFrag();
		int getExp();
		int getExpEarned();
		int getExpRequired();

		void incDie();
		void incExp();
		void incFrag();

		void setExpEarned(int expEarned);


	private:
		int m_level, m_nb_die, m_nb_frag, m_exp, m_expEarned, m_expRequired;
	};
}


#endif /* PLAYER_HPP_ */
