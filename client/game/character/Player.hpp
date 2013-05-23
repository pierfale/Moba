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
#include "../spell/Spell.h"

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
		Spell* getSpell();
		std::vector<int> getIDSpell();


	private:
		int m_level;
		Spell* m_spell;
		std::vector<int> m_idSpell;
	};
}


#endif /* PLAYER_HPP_ */
