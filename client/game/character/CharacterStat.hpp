/*
 * CharacterStat.hpp
 *
 *  Created on: 7 mai 2013
 *      Author: pierre
 */

#ifndef CHARACTERSTAT_HPP_
#define CHARACTERSTAT_HPP_

namespace game {

	class CharacterStat {

	public:
		CharacterStat();

		void setLife(int value);
		void setMaxLife(int value);
		void setMana(int value);
		void setMaxMana(int value);
		void setAttackSpeed(float value);
		void setMovementSpeed(float value);
		void setPhysicalAttack(int value);
		void setMagicalAttack(int value);
		void setPhysicalArmor(int value);
		void setMagicalArmor(int value);
		void setRange(float value);

		int life();
		int maxLife();
		int mana();
		int maxMana();
		float attackSpeed();
		float movementSpeed();
		int physicalAttack();
		int magicalAttack();
		int physicalArmor();
		int magicalArmor();
		float range();

	protected:
		int m_life;
		int m_maxLife;
		int m_maxMana;
		int m_mana;

		float m_attackSpeed;
		float m_movementSpeed;

		int m_physicalAttack;
		int m_magicalAttack;

		int m_physicalArmor;
		int m_magicalArmor;

		float m_range;
	};
}


#endif /* CHARACTERSTAT_HPP_ */
