/*
 * CharacterInfo.cpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#include "CharacterInfo.hpp"

namespace graphics {

	CharacterInfo::CharacterInfo(game::Player* player) : m_player(player) {
	}

	void CharacterInfo::load() {
		this->setBackgroundColor(sf::Color(30, 30, 30));
		this->setLayout(new PassivLayout());

		BasicStyle* labelstyle = new BasicStyle();
		labelstyle->setFontColor(sf::Color::White);

		Label* name = new Label(m_player->getName(), labelstyle);
		name->setCoord(util::Coordinates(0, 10));
		name->setMinimalSize();
		this->add(name);
		name->setWidthCenter();

		Label* physicalAttack = new Label("Physical Attack : "+util::Cast::intToString(m_player->getStat()->physicalAttack()), labelstyle);
		physicalAttack->setCoord(util::Coordinates(10, 40));
		physicalAttack->setMinimalSize();
		this->add(physicalAttack);

		Label* magicalAttack = new Label("Magical Attack : "+util::Cast::intToString(m_player->getStat()->magicalAttack()), labelstyle);
		magicalAttack->setCoord(util::Coordinates(10, 70));
		magicalAttack->setMinimalSize();
		this->add(magicalAttack);

		Label* physicalArmor = new Label("Physical Armor : "+util::Cast::intToString(m_player->getStat()->physicalArmor()), labelstyle);
		physicalArmor->setCoord(util::Coordinates(10, 100));
		physicalArmor->setMinimalSize();
		this->add(physicalArmor);

		Label* magicalArmor = new Label("Magical Armor : "+util::Cast::intToString(m_player->getStat()->magicalArmor()), labelstyle);
		magicalArmor->setCoord(util::Coordinates(10, 130));
		magicalArmor->setMinimalSize();
		this->add(magicalArmor);

		Label* attackSpeed = new Label("Attack Speed : "+util::Cast::intToString(m_player->getStat()->attackSpeed()), labelstyle);
		attackSpeed->setCoord(util::Coordinates(10, 160));
		attackSpeed->setMinimalSize();
		this->add(attackSpeed);

		Label* speed = new Label("Movement Speed : "+util::Cast::intToString(m_player->getStat()->movementSpeed()), labelstyle);
		speed->setCoord(util::Coordinates(10, 190));
		speed->setMinimalSize();
		this->add(speed);
	}
}


