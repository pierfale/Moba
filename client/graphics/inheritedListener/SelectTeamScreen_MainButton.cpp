/*
 * SelectTeamScreen_MainButton.cpp
 *
 *  Created on: 27 avr. 2013
 *      Author: pierre
 */

#include "SelectTeamScreen_MainButton.hpp"

namespace graphics {

	SelectTeamScreen_MainButton::SelectTeamScreen_MainButton(SelectTeamScreen* view) : m_view(view) {

	}

	void SelectTeamScreen_MainButton::pressed(void* origin) {
		m_view->buttonPressed(origin);
	}
}


