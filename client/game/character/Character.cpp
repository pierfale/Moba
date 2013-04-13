/*
 * Character.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#include "Character.hpp"

namespace game {

	Character::Character(std::string name) : m_name(name) {

	}

	std::string	Character::getName() {
		return m_name;
	}
};


