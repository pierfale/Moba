/*
 * PlayerStat.hpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#ifndef PLAYERSTAT_HPP_
#define PLAYERSTAT_HPP_

#include <string>

class Client;
class Player;

class PlayerStat {

public:
	PlayerStat(Client* client);
	void reset();

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

	void changeLife(int value, bool send = true);
	void changePhysicalAttack(int value, bool send = true);
	void changeMagicalAttack(int value, bool send = true);
	void changeAttackSpeed(float value, bool send = true);
	void changeMovementSpeed(float value, bool send = true);
	void changePhysicalArmor(int value, bool send = true);
	void changeMagicalArmor(int value, bool send = true);
	void changeRange(float value, bool send = true);

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

private:
	Client* m_client;

	int m_life;
	int m_maxLife;
	int m_mana;
	int m_maxMana;

	float m_attackSpeed;
	float m_movementSpeed;

	int m_physicalAttack;
	int m_magicalAttack;

	int m_physicalArmor;
	int m_magicalArmor;

	float m_range;
};

#endif /* PLAYERSTAT_HPP_ */
