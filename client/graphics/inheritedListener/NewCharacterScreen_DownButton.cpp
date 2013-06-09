/*
 * NewCharacterScreen_DownButton.cpp
 *
 *  Created on: 15 avr. 2013
 *      Author: pierre
 */

#include "NewCharacterScreen_DownButton.hpp"

namespace graphics {

	NewCharacterScreen_DownButton::NewCharacterScreen_DownButton(NewCharacterScreen* view) : m_view(view) {

	}

	void NewCharacterScreen_DownButton::pressed(void* origin) {
		m_view->buttonChanged(origin);
	}
}




