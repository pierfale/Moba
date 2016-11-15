/*
 * CreateGameScreen_DownButton.cpp
 *
 *  Created on: 23 avr. 2013
 *      Author: pierre
 */

#include "CreateGameScreen_DownButton.hpp"

namespace graphics {

	CreateGameScreen_DownButton::CreateGameScreen_DownButton(CreateGameScreen* view) : m_view(view) {

	}

	void CreateGameScreen_DownButton::pressed(void* origin) {
		m_view->buttonChanged(origin);
	}
}






