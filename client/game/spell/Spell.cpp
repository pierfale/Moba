/*
 * Spell.cpp
 *
 *  Created on: 22 avr. 2013
 *      Author: Béni
 */

#include "Spell.h"
#include "../character/Player.hpp"

namespace game {

	Spell::Spell() : m_cast(false), m_range(0) { m_player = NULL;}
	Spell::Spell(Player* player) : m_cast(false), m_range(0)  {m_player = player;}
	Spell::~Spell() {}

	void Spell::callSpell(int id, Player* target) {
		autoAttack(target);
	}

	void Spell::autoAttack(Player* target) {
		m_range = 50;
		m_cast = true;
	}

	bool Spell::getCast() {return m_cast;}
	bool Spell::onRange(Player* target) {
		if (abs(m_player->getCoord().x - target->getCoord().x) <= m_range &&
			abs(m_player->getCoord().y - target->getCoord().y) <= m_range)
				return true;
		return false;
	}
	void Spell::setCast(bool cast) {m_cast = cast;}


} /* namespace game */
