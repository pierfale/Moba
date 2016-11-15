/*
 * SingleTargetSpell.cpp
 *
 *  Created on: 8 mai 2013
 *      Author: pierre
 */

#include "SingleTargetSpellAnim.hpp"
#include "SingleTargetSpellImpl.hpp"
#include "ShotImpl.hpp"

namespace graphics {

	SingleTargetSpellAnim::SingleTargetSpellAnim(game::Character* caster, game::Character* target) {
		m_caster = caster;
		m_target = target;
	}

	SingleTargetSpellAnim* SingleTargetSpellAnim::process(int idSpell, game::Character* caster, game::Character* target) {
		switch(idSpell) {
			case 1:
				return new AutoAttackAnim(caster, target);
			case 2:
				return new ArrowAnim(caster, target);
			case 10:
				return new AutoAttackAnim(caster, target);
			case 11:
				return new FireBallAnim(caster, target);
		}
		return NULL;
	}
}
