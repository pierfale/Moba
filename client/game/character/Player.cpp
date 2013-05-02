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
		 m_direction = network::PacketType::DIRECTION_NONE;
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

	util::CoordFloat Player::getCoord() {
		return m_coord;
	}

	void Player::setCoord(util::CoordFloat coord){
		m_coord = coord;
	}

	void Player::setCoordExtra(util::CoordFloat coord) {
		m_coordExtra = util::CoordFloat(m_coordExtra.x+coord.x, m_coordExtra.y+coord.y);
	}

	util::CoordFloat Player::getCoordExtra() {
		util::CoordFloat coord;
		if(m_coordExtra.x != 0) {
			if(m_coordExtra.x > 0)
				coord.x = m_coordExtra.x - PLAYER_EXTRA_COORD > 0 ? PLAYER_EXTRA_COORD : m_coordExtra.x;
			else
				coord.x = m_coordExtra.x + PLAYER_EXTRA_COORD < 0 ? PLAYER_EXTRA_COORD : m_coordExtra.x;
		}
		if(m_coordExtra.y != 0) {
			if(m_coordExtra.y > 0)
				coord.y = m_coordExtra.y - PLAYER_EXTRA_COORD > 0 ? PLAYER_EXTRA_COORD : m_coordExtra.y;
			else
				coord.y = m_coordExtra.y + PLAYER_EXTRA_COORD < 0 ? PLAYER_EXTRA_COORD : m_coordExtra.y;
		}
		m_coordExtra = util::CoordFloat(m_coordExtra.x-coord.x, m_coordExtra.y-coord.y);
		return coord;
	}

	Spell* Player::getSpell() {
		return m_spell;
	}

	std::vector<int> Player::getIDSpell() {
		return m_idSpell;
	}

	network::PacketType::PacketContents Player::getDirection() {
		return m_direction;
	}

	void Player::setDirection(network::PacketType::PacketContents dir) {
		m_direction = dir;
	}
}


