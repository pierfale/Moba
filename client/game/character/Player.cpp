/*
 * Player.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#include "Player.hpp"

namespace game {

	Player::Player(int id, std::string name, int level) : Character(id, name), m_level(level) {
		 m_spell = new Spell(this);
		 m_idSpell.push_back(1);m_idSpell.push_back(2);
		 m_stat = new PlayerStat();
	}

	PlayerStat* Player::getStat() {
		return (PlayerStat*)m_stat;
	}

	int Player::getLevel() {
		return m_level;
	}

	Spell* Player::getSpell() {
		return m_spell;
	}

	std::vector<int> Player::getIDSpell() {
		return m_idSpell;
	}
}


