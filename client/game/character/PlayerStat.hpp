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

		float attackSpeed();
		float movementSpeed();

		int physicalAttack();
		int magicalAttack();

		int physicalArmor();
		int magicalArmor();

	private:
		float m_attackSpeed;
		float m_movementSpeed;

		int m_physicalAttack;
		int m_magicalAttack;

		int m_physicalArmor;
		int m_magicalArmor;
	};
}


#endif /* PLAYERSTAT_HPP_ */
