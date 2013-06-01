/*
 * CharacterStat.cpp
 *
 *  Created on: 7 mai 2013
 *      Author: pierre
 */

#include "CharacterStat.hpp"

namespace game {

	CharacterStat::CharacterStat() {
		m_life = 0;
		m_maxLife = 0;
		m_mana = 0;
		m_maxMana = 0;

		m_attackSpeed = 0.0;
		m_movementSpeed = 0.0;

		m_physicalAttack = 0;
		m_magicalAttack = 0;

		m_physicalArmor = 0;
		m_magicalArmor = 0;

		m_range = 0.0;
	}

	void CharacterStat::setLife(int value) {
		m_life = value;
	}

	void CharacterStat::setMaxLife(int value) {
		m_maxLife = value;
	}

	void CharacterStat::setMana(int value) {
		m_mana = value;
	}

	void CharacterStat::setMaxMana(int value) {
		m_maxMana = value;
	}

	void CharacterStat::setAttackSpeed(float value) {
		m_attackSpeed = value;
	}

	void CharacterStat::setMovementSpeed(float value) {
		m_movementSpeed = value;
	}

	void CharacterStat::setPhysicalAttack(int value) {
		m_physicalAttack = value;
	}

	void CharacterStat::setMagicalAttack(int value) {
		m_magicalAttack = value;
	}

	void CharacterStat::setPhysicalArmor(int value) {
		m_physicalArmor = value;
	}

	void CharacterStat::setMagicalArmor(int value) {
		m_magicalArmor = value;
	}

	void CharacterStat::setRange(float value) {
		m_range = value;
	}

	int CharacterStat::life() {
		return m_life;
	}

	int CharacterStat::maxLife() {
		return m_maxLife;
	}

	int CharacterStat::mana() {
		return m_mana;
	}

	int CharacterStat::maxMana() {
		return m_maxMana;
	}

	float CharacterStat::attackSpeed() {
		return m_attackSpeed;
	}

	float CharacterStat::movementSpeed() {
		return m_movementSpeed;
	}

	int CharacterStat::physicalAttack() {
		return m_physicalAttack;
	}

	int CharacterStat::magicalAttack() {
		return m_magicalAttack;
	}

	int CharacterStat::physicalArmor() {
		return m_physicalArmor;
	}

	int CharacterStat::magicalArmor() {
		return m_magicalArmor;
	}

	float CharacterStat::range() {
		return m_range;
	}
}


