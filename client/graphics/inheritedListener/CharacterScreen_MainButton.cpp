/*
 * CharacterScreen_MainButton.cpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#include "CharacterScreen_MainButton.hpp"

namespace graphics {

	CharacterScreen_MainButton::CharacterScreen_MainButton(CharacterScreen* view) : m_view(view) {

	}

	void CharacterScreen_MainButton::pressed(void* origin) {
		m_view->viewChanged(origin);
	}
}


