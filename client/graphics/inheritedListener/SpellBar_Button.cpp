/*
 * SpellBar_Button.cpp
 *
 *  Created on: 28 mai 2013
 *      Author: pierre
 */

#include "SpellBar_Button.hpp"

namespace graphics {

	SpellBar_Button::SpellBar_Button(SpellBarr* view) : m_view(view) {

	}

	void SpellBar_Button::pressed(void* origin) {
		m_view->spellActivate(origin);
	}

}




