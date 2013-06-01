/*
 * SingleTargetSpell.cpp
 *
 *  Created on: 8 mai 2013
 *      Author: pierre
 */

#include "SingleTargetSpellAnim.hpp"

namespace graphics {

	SingleTargetSpellAnim::SingleTargetSpellAnim(game::Character* caster, game::Character* target) {
		m_caster = caster;
		m_target = target;
	}
}
