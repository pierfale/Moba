/*
 * Player.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#include "Player.hpp"

namespace game {

	Player::Player(int id, std::string name, int level) : Character(name), m_id(id), m_level(level), m_team(0) {
		 m_spell = new Spell(this);
		 m_idSpell.push_back(1);m_idSpell.push_back(2);//TODO erase
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

	int Player::getTeam() {
		return m_team;
	}

	void Player::setTeam(int team) {
		m_team = team;
	}

	util::Coordinates Player::getCoord() {
		return m_coord;
	}

	void Player::setCoord(int x, int y){
		m_coord.x = x ; m_coord.y = y;
	}

	Spell* Player::getSpell() {
		return m_spell;
	}

	std::vector<int> Player::getIDSpell() {
		return m_idSpell;
	}


}


