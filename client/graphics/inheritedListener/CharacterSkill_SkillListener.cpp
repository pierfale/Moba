/*
 * CharacterSkill_SkillListener.cpp
 *
 *  Created on: 25 mai 2013
 *      Author: pierre
 */

#include "CharacterSkill_SkillListener.hpp"

namespace graphics {

	CharacterSkill_SkillListener::CharacterSkill_SkillListener(CharacterSkill* view) : m_view(view) {

	}

	void CharacterSkill_SkillListener::pressed(void* origin) {
		m_view->skillPressed(origin);
	}

}


