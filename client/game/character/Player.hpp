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

namespace game {

	class Player : public Character {

	public:
		Player(int id, std::string name, int level);
		PlayerStat* getStat();
		int getLevel();

	private:
		int m_id;
		int m_level;
		PlayerStat* m_stat;

	};
}


#endif /* PLAYER_HPP_ */
