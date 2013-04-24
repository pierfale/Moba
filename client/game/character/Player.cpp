/*
 * Player.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#include "Player.hpp"

namespace game {

	Player::Player(int id, std::string name, int level) : Character(name), m_id(id), m_level(level) {
	}

	int Player::getID() {
		return m_id;
	}

	PlayerStat* Player::getStat() {
		return &m_stat;
	}

	int Player::getLevel() {
		return m_level;
	}
}


