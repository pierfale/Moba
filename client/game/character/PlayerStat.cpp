/*
 * PlayerStat.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#include "PlayerStat.hpp"

namespace game {

	PlayerStat::PlayerStat() {
		m_attackSpeed = 0;
		m_movementSpeed = 100;

		m_physicalAttack = 0;
		m_magicalAttack = 0;

		m_physicalArmor = 0;
		m_magicalArmor = 0;
	}

	float PlayerStat::attackSpeed() {
		return m_attackSpeed;
	}

	float PlayerStat::movementSpeed() {
		return m_movementSpeed;
	}

	int PlayerStat::physicalAttack() {
		return m_physicalAttack;
	}

	int PlayerStat::magicalAttack() {
		return m_magicalAttack;
	}

	int PlayerStat::physicalArmor() {
		return m_physicalArmor;
	}

	int PlayerStat::magicalArmor() {
		return m_magicalArmor;
	}
}


