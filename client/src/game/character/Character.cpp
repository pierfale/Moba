/*
 * Character.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#include "Character.hpp"

namespace game {

	const float Character::m_extraCoordNb = 1.0;

	Character::Character(int id, std::string name) : m_id(id), m_name(name) {
		 m_direction = network::PacketType::DIRECTION_NONE;
		 m_faction = network::PacketType::FACTION_PEACEFUL;
		 m_stat = new CharacterStat();
	}

	Character::~Character() {
		delete m_stat;
	}

	int Character::getID() {
		return m_id;
	}

	std::string	Character::getName() {
		return m_name;
	}

	util::CoordFloat Character::getCoord() {
		return m_coord;
	}

	network::PacketType::PacketContents Character::getFaction() {
		return m_faction;
	}

	network::PacketType::PacketContents Character::getDirection() {
		return m_direction;
	}

	CharacterStat* Character::getStat() {
		return m_stat;
	}

	void Character::setCoord(util::CoordFloat coord){
		m_coord = coord;
	}

	void Character::setCoordExtra(util::CoordFloat coord) {
		m_coordExtra = coord;
	}

	util::CoordFloat Character::getCoordExtra() {
		util::CoordFloat coord;
		if(m_coordExtra.x != 0) {
			if(m_coordExtra.x > 0)
				coord.x = m_coordExtra.x - m_extraCoordNb > 0 ? m_extraCoordNb : m_coordExtra.x;
			else
				coord.x = m_coordExtra.x + m_extraCoordNb < 0 ? -m_extraCoordNb : m_coordExtra.x;
		}
		if(m_coordExtra.y != 0) {
			if(m_coordExtra.y > 0)
				coord.y = m_coordExtra.y - m_extraCoordNb > 0 ? m_extraCoordNb : m_coordExtra.y;
			else
				coord.y = m_coordExtra.y + m_extraCoordNb < 0 ? -m_extraCoordNb : m_coordExtra.y;
		}
		m_coordExtra = util::CoordFloat(m_coordExtra.x-coord.x, m_coordExtra.y-coord.y);
		return coord;
	}

	void Character::setDirection(network::PacketType::PacketContents dir) {
		m_direction = dir;
	}

	void Character::setFaction(network::PacketType::PacketContents faction) {
		m_faction = faction;
	}
};


