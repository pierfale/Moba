/*
 * Case.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: Béni
 */

#include "Case.h"

namespace game {

	Case::Case() : m_passable(true) , m_id(-1){}
	Case::Case(int id) : m_passable(true) , m_id(id){}
	Case::~Case() {}

	int Case::getId() {return m_id;}

	void Case::setPassable(bool passable) { m_passable = passable; }
	bool Case::getPassable() { return m_passable; }

} /* namespace game */
