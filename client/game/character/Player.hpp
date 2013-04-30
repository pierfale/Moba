/*
 * Player.hpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Character.hpp"
#include "PlayerStat.hpp"
#include "../spell/Spell.h"
#include "../../util/Coordinates.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace game {

	class Player : public Character {

	public:
		Player(int id, std::string name, int level);
		int getID();
		PlayerStat* getStat();
		int getLevel();
		int getTeam();
		void setTeam(int team);
		Spell* getSpell();
		util::Coordinates getCoord();
		std::vector<int> getIDSpell();

		//setters
		void setCoord(int x, int y);

	private:
		int m_id;
		int m_level;
		PlayerStat m_stat;
		int m_team;
		util::Coordinates m_coord;
		Spell* m_spell;
		std::vector<int> m_idSpell;
	};
}


#endif /* PLAYER_HPP_ */
