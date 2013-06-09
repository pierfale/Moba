/*
 * CharacterScreen_CharacterButton.cpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#include "CharacterScreen_CharacterButton.hpp"

namespace graphics {

	CharacterScreen_CharacterButton::CharacterScreen_CharacterButton(CharacterScreen* view) : m_view(view) {

	}

	void CharacterScreen_CharacterButton::pressed(void* origin) {
		m_view->characterChanged(origin);
	}

}


