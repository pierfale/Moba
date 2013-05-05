/*
 * PlayerStat.hpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#ifndef PLAYERSTAT_HPP_
#define PLAYERSTAT_HPP_

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace game {

	class PlayerStat {

	public:
		PlayerStat();

		void setLife(int value);
		void setMana(int value);
		void setAttackSpeed(int value);
		void setMovementSpeed(int value);
		void setPhysicalAttack(int value);
		void setMagicalAttack(int value);
		void setPhysicalArmor(int value);
		void setMagicalArmor(int value);
		void setRange(int value);

		int life();
		int mana();
		float attackSpeed();
		float movementSpeed();
		int physicalAttack();
		int magicalAttack();
		int physicalArmor();
		int magicalArmor();
		float range();

	private:
		int m_life;
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


#endif /* PLAYERSTAT_HPP_ */
