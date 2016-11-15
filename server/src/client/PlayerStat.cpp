/*
 * PlayerStat.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#include "PlayerStat.hpp"
#include "Client.hpp"
#include "../game/Game.hpp"
#include "Player.hpp"

	PlayerStat::PlayerStat(Client* client) : m_client(client) {
		reset();
	}

	void PlayerStat::reset() {
		m_life = 100;
		m_maxLife = 100;
		m_mana = 100;
		m_maxMana = 100;

		m_attackSpeed = 1.0;
		m_movementSpeed = 100.0;

		m_physicalAttack = 5;
		m_magicalAttack = 5;

		m_physicalArmor = 0;
		m_magicalArmor = 0;

		m_range = 100.0;
	}

	void PlayerStat::setLife(int value) {
		m_life = value;
	}

	void PlayerStat::setMaxLife(int value) {
		m_maxLife = value;
	}

	void PlayerStat::setMana(int value) {
		m_mana = value;
	}


	void PlayerStat::setMaxMana(int value) {
		m_maxMana = value;
	}

	void PlayerStat::setAttackSpeed(float value) {
		m_attackSpeed = value;
	}

	void PlayerStat::setMovementSpeed(float value) {
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

	void PlayerStat::setRange(float value) {
		m_range = value;
	}

	void PlayerStat::changeLife(int value, bool send) {
		m_life = m_life+value > 0 ? m_life+value : 0;

		if(send) {
			network::Packet packet(NULL, network::PacketType::GAME_STAT_LIFE);
			packet << m_client->getCharacter()->getID() << m_life;
			m_client->getGame()->sendAll(packet);
		}
	}

	void PlayerStat::changePhysicalAttack(int value, bool send) {
		m_physicalAttack += value;

		if(send) {
			network::Packet packet(NULL, network::PacketType::GAME_STAT_PHYSICALATTACK);
			packet << m_client->getCharacter()->getID() << m_physicalAttack;
			m_client->getGame()->sendAll(packet);
		}
	}

	void PlayerStat::changeMagicalAttack(int value, bool send) {
		m_magicalAttack += value;

		if(send) {
			network::Packet packet(NULL, network::PacketType::GAME_STAT_MAGICALATTACK);
			packet << m_client->getCharacter()->getID() << m_magicalAttack;
			m_client->getGame()->sendAll(packet);
		}
	}

	void PlayerStat::changeAttackSpeed(float value, bool send) {
		m_attackSpeed += value;

		if(send) {
			network::Packet packet(NULL, network::PacketType::GAME_STAT_ATTACKSPEED);
			packet << m_client->getCharacter()->getID() << m_attackSpeed;
			m_client->getGame()->sendAll(packet);
		}
	}

	void PlayerStat::changeMovementSpeed(float value, bool send) {
		m_movementSpeed += value;

		if(send) {
			network::Packet packet(NULL, network::PacketType::GAME_STAT_MOVEMENTSPEED);
			packet << m_client->getCharacter()->getID() << m_movementSpeed;
			m_client->getGame()->sendAll(packet);
		}
	}

	void PlayerStat::changePhysicalArmor(int value, bool send) {
		m_physicalArmor += value;

		if(send) {
			network::Packet packet(NULL, network::PacketType::GAME_STAT_PHYSICALARMOR);
			packet << m_client->getCharacter()->getID() << m_physicalArmor;
			m_client->getGame()->sendAll(packet);
		}
	}

	void PlayerStat::changeMagicalArmor(int value, bool send) {
		m_magicalArmor += value;

		if(send) {
			network::Packet packet(NULL, network::PacketType::GAME_STAT_MAGICALARMOR);
			packet << m_client->getCharacter()->getID() << m_magicalArmor;
			m_client->getGame()->sendAll(packet);
		}
	}

	void PlayerStat::changeRange(float value, bool send) {
		m_range += value;

		if(send) {
			network::Packet packet(NULL, network::PacketType::GAME_STAT_RANGE);
			packet << m_client->getCharacter()->getID() << m_range;
			m_client->getGame()->sendAll(packet);
		}
	}

	int PlayerStat::life() {
		return m_life;
	}

	int PlayerStat::maxLife() {
		return m_maxLife;
	}

	int PlayerStat::mana() {
		return m_mana;
	}

	int PlayerStat::maxMana() {
		return m_maxMana;
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

