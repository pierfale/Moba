/*
 * SingleTargetSpell.cpp
 *
 *  Created on: 4 mai 2013
 *      Author: pierre
 */

#include "SingleTargetSpell.hpp"

	boost::shared_ptr<SingleTargetSpell> SingleTargetSpell::m_instance;

	SingleTargetSpell::SingleTargetSpell() {
		m_spells[1] = boost::bind(&SingleTargetSpell::autoAttack, this, _1, _2);
		m_spells[10] = boost::bind(&SingleTargetSpell::spell10, this, _1, _2);
		m_spells[11] = boost::bind(&SingleTargetSpell::spell11, this, _1, _2);
	}

	bool SingleTargetSpell::process(int idSpell, Player* caster, Player* target) {
		if(getInstance()->m_spells.find(idSpell) != getInstance()->m_spells.end()) {
			return getInstance()->m_spells[idSpell](caster, target);
		}
		else
			log_err "Non-existent spell id="+util::Cast::intToString(idSpell) end_log_err;
		return false;
	}

	bool SingleTargetSpell::autoAttack(Player* caster, Player* target) {
		if(caster->getTeam() != target->getTeam()) {
			if(util::Math::distance(caster->getCoord(), target->getCoord()) <= caster->getStat()->range()
					&& caster->getCooldown(1) >= caster->getStat()->attackSpeed()) {
				target->setPhysicalDamage(caster->getStat()->physicalAttack(), caster);
				caster->resetCooldown(1);
				return true;
			}
		}
		return false;
	}

	bool SingleTargetSpell::spell10(Player* caster, Player* target) {
		return launchSpell(caster, target, 10, caster->getStat()->range(), 10.0, false, caster->getStat()->physicalAttack()*2);
	}

	bool SingleTargetSpell::spell11(Player* caster, Player* target) {
		return launchSpell(caster, target, 11, 300.0, 10.0, false, caster->getStat()->magicalAttack()*2);
	}

	bool SingleTargetSpell::launchSpell(Player* caster, Player* target, int id, float range, float cooldowns, bool isPhysical, int damage) {
		if(caster->getTeam() != target->getTeam() && caster->hasSpell(id)) {
			if(util::Math::distance(caster->getCoord(), target->getCoord()) <= range) {
				if(caster->getCooldown(id) >= cooldowns) {
					if(isPhysical)
						target->setPhysicalDamage(damage, caster);
					else
						target->setMagicalDamage(damage, caster);
					caster->resetCooldown(id);
					return true;
				}
				else
					caster->sendMessage("the spell is not yet charged");
			}
			else
				caster->sendMessage("the target is out of range");
		}
		return false;
	}


	SingleTargetSpell* SingleTargetSpell::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new SingleTargetSpell());
		return m_instance.get();
	}


