/*
 * Player.hpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "PacketType.hpp"
#include "Character.hpp"
#include "PlayerStat.hpp"
#include "../spell/Spell.h"
#include "../../util/Coordinates.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

#define PLAYER_EXTRA_COORD 1.0

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
		util::CoordFloat getCoord();
		util::CoordFloat getCoordExtra();
		std::vector<int> getIDSpell();
		network::PacketType::PacketContents getDirection();

		//setters
		void setCoord(util::CoordFloat coord);
		void setCoordExtra(util::CoordFloat coord);
		void setDirection(network::PacketType::PacketContents dir);


	private:
		int m_id;
		int m_level;
		PlayerStat m_stat;
		int m_team;
		util::CoordFloat m_coord;
		util::CoordFloat m_coordExtra;
		network::PacketType::PacketContents m_direction;
		Spell* m_spell;
		std::vector<int> m_idSpell;
	};
}


#endif /* PLAYER_HPP_ */
