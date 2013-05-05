/*
 * PlayerStat.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#include "PlayerStat.hpp"

namespace game {

	PlayerStat::PlayerStat() {
		m_life = 0;
		m_mana = 0;

		m_attackSpeed = 0.0;
		m_movementSpeed = 0.0;

		m_physicalAttack = 0;
		m_magicalAttack = 0;

		m_physicalArmor = 0;
		m_magicalArmor = 0;

		m_range = 0.0;
	}

	void PlayerStat::setLife(int value) {
		m_life = value;
	}

	void PlayerStat::setMana(int value) {
		m_mana = value;
	}

	void PlayerStat::setAttackSpeed(int value) {
		m_attackSpeed = value;
	}

	void PlayerStat::setMovementSpeed(int value) {
		m_movementSpeed = value;
	}

	void PlayerStat::setPhysicalAttack(int value) {
		m_physicalAttack = value;
	}

	void PlayerStat::setMagicalAttack(int value) {
		m_magicalAttack = value;
	}

	void PlayerStat::setPhysicalArmor(int value) {
		m_physicalArmor = value;
	}

	void PlayerStat::setMagicalArmor(int value) {
		m_magicalArmor = value;
	}

	void PlayerStat::setRange(int value) {
		m_range = value;
	}

	int PlayerStat::life() {
		return m_life;
	}

	int PlayerStat::mana() {
		return m_mana;
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

	float PlayerStat::range() {
		return m_range;
	}
}


