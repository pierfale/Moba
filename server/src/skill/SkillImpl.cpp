/*
 * SkillImpl.cpp
 *
 *  Created on: 27 mai 2013
 *      Author: pierre
 */

#include "SkillImpl.hpp"

boost::shared_ptr<SkillImpl> SkillImpl::m_instance;

SkillImpl::SkillImpl() {
	m_skills[1] = boost::bind(&SkillImpl::skill1, this, _1);
	m_skills[2] = boost::bind(&SkillImpl::skill2, this, _1);
	m_skills[3] = boost::bind(&SkillImpl::skill3, this, _1);
	m_skills[4] = boost::bind(&SkillImpl::skill4, this, _1);
	m_skills[5] = boost::bind(&SkillImpl::skill5, this, _1);
	m_skills[6] = boost::bind(&SkillImpl::skill6, this, _1);
	m_skills[7] = boost::bind(&SkillImpl::skill7, this, _1);
	m_skills[8] = boost::bind(&SkillImpl::skill8, this, _1);
	m_skills[9] = boost::bind(&SkillImpl::skill9, this, _1);
	m_skills[10] = boost::bind(&SkillImpl::skill10, this, _1);
	m_skills[11] = boost::bind(&SkillImpl::skill11, this, _1);
}

void SkillImpl::process(int id, Player* player) {
	if(getInstance()->m_skills.find(id) != getInstance()->m_skills.end()) {
		getInstance()->m_skills[id](player);
	}
	else
		log_err "Non-existent skill id="+util::Cast::intToString(id) end_log_err;
}

//Way of Warrior
void SkillImpl::skill1(Player* player) {
	player->getStat()->changePhysicalAttack(5, false);
}

//Way of Mage
void SkillImpl::skill2(Player* player) {
	player->getStat()->changeMagicalAttack(5, false);
}

//PowerFul Strike
void SkillImpl::skill3(Player* player) {
	player->addSpell(10);
}

void SkillImpl::skill4(Player* player) {
	player->getStat()->changePhysicalAttack(3, false);
	player->getStat()->changeRange(100, false);
}

void SkillImpl::skill5(Player* player) {
	player->addSpell(11);
}

void SkillImpl::skill6(Player* player) {
	player->addSpell(12);
}

void SkillImpl::skill7(Player* player) {
	player->getStat()->changePhysicalArmor(5, false);
	player->getStat()->changeMagicalArmor(5, false);
}

void SkillImpl::skill8(Player* player) {
	player->getStat()->changeAttackSpeed(player->getStat()->range()*1.3, false);
}

void SkillImpl::skill9(Player* player) {
	player->addSpell(13);
}

void SkillImpl::skill10(Player* player) {
	player->addSpell(14);
}

void SkillImpl::skill11(Player* player) {
	player->addSpell(15);
}

SkillImpl* SkillImpl::getInstance() {
	if(m_instance.get() == NULL)
		m_instance.reset(new SkillImpl());
	return m_instance.get();
}
