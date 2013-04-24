/*
 * GameListScreen_MainButton.cpp
 *
 *  Created on: 16 avr. 2013
 *      Author: pierre
 */

#include "GameListScreen_MainButton.hpp"

namespace graphics {

	GameListScreen_MainButton::GameListScreen_MainButton(GameListScreen* view) : m_view(view) {

	}

	void GameListScreen_MainButton::pressed(void* origin) {
		m_view->buttonPressed(origin);
	}
}


