/*
 * CharacterInfo.cpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#include "CharacterInfo.hpp"

namespace graphics {

	CharacterInfo::CharacterInfo(game::Player* player) : m_player(player) {
		m_physicalAttack = NULL;
		m_magicalAttack = NULL;
		m_physicalArmor = NULL;
		m_magicalArmor = NULL;
		m_attackSpeed = NULL;
		m_speed = NULL;
	}

	CharacterInfo::~CharacterInfo() {
		delete m_labelstyle;
		delete m_name;
		delete m_life;
		delete m_mana;
		delete m_physicalAttack;
		delete m_magicalAttack;
		delete m_physicalArmor;
		delete m_magicalArmor;
		delete m_attackSpeed;
		delete m_speed;
	}

	void CharacterInfo::load() {
		network::Packet packet(network::Network::getSocket(), network::PacketType::SESSION_ASKALLSTAT);
		packet.send();

		this->setBackgroundColor(sf::Color(30, 30, 30));
		this->setLayout(new PassivLayout());

		m_labelstyle = new BasicStyle();
		m_labelstyle->setFontColor(sf::Color::White);

		m_name = new Label(m_player->getName(), m_labelstyle);
		m_name->setCoord(util::CoordInt(0, 10));
		m_name->setMinimalSize();
		this->add(m_name);
		m_name->setWidthCenter();

		m_life = new Label("Life : "+util::Cast::intToString(m_player->getStat()->life()), m_labelstyle);
		m_life->setCoord(util::CoordInt(10, 40));
		m_life->setMinimalSize();
		this->add(m_life);

		m_mana= new Label("Mana : "+util::Cast::intToString(m_player->getStat()->mana()), m_labelstyle);
		m_mana->setCoord(util::CoordInt(10, 70));
		m_mana->setMinimalSize();
		this->add(m_mana);

		m_physicalAttack = new Label("Physical Attack : "+util::Cast::intToString(m_player->getStat()->physicalAttack()), m_labelstyle);
		m_physicalAttack->setCoord(util::CoordInt(10, 100));
		m_physicalAttack->setMinimalSize();
		this->add(m_physicalAttack);

		m_magicalAttack = new Label("Magical Attack : "+util::Cast::intToString(m_player->getStat()->magicalAttack()), m_labelstyle);
		m_magicalAttack->setCoord(util::CoordInt(10, 130));
		m_magicalAttack->setMinimalSize();
		this->add(m_magicalAttack);

		m_physicalArmor = new Label("Physical Armor : "+util::Cast::intToString(m_player->getStat()->physicalArmor()), m_labelstyle);
		m_physicalArmor->setCoord(util::CoordInt(10, 160));
		m_physicalArmor->setMinimalSize();
		this->add(m_physicalArmor);

		m_magicalArmor = new Label("Magical Armor : "+util::Cast::intToString(m_player->getStat()->magicalArmor()), m_labelstyle);
		m_magicalArmor->setCoord(util::CoordInt(10, 190));
		m_magicalArmor->setMinimalSize();
		this->add(m_magicalArmor);

		m_attackSpeed = new Label("Attack Speed : "+util::Cast::floatToString(m_player->getStat()->attackSpeed()), m_labelstyle);
		m_attackSpeed->setCoord(util::CoordInt(10, 220));
		m_attackSpeed->setMinimalSize();
		this->add(m_attackSpeed);

		m_speed = new Label("Movement Speed : "+util::Cast::floatToString(m_player->getStat()->movementSpeed()), m_labelstyle);
		m_speed->setCoord(util::CoordInt(10, 250));
		m_speed->setMinimalSize();
		this->add(m_speed);
	}

	void CharacterInfo::refresh() {
		m_life->setText("Life : "+util::Cast::intToString(m_player->getStat()->life()));
		m_mana->setText("Mana : "+util::Cast::intToString(m_player->getStat()->mana()));
		m_physicalAttack->setText("Physical Attack : "+util::Cast::intToString(m_player->getStat()->physicalAttack()));
		m_magicalAttack->setText("Magical Attack : "+util::Cast::intToString(m_player->getStat()->magicalAttack()));
		m_physicalArmor->setText("Physical Armor : "+util::Cast::intToString(m_player->getStat()->physicalArmor()));
		m_magicalArmor->setText("Magical Armor : "+util::Cast::intToString(m_player->getStat()->magicalArmor()));
		m_attackSpeed->setText("Attack Speed : "+util::Cast::floatToString(m_player->getStat()->attackSpeed()));
		m_speed->setText("Movement Speed : "+util::Cast::floatToString(m_player->getStat()->movementSpeed()));
	}

	std::string CharacterInfo::getComponentName() {
		return "CharacterInfo";
	}

	std::string CharacterInfo::getName() {
		return "CharacterInfo";
	}
}


