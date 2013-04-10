/*
 * ConnectionScreen_Button.cpp
 *
 *  Created on: 9 avr. 2013
 *      Author: pierre
 */

#include "ConnectionScreen_Button.hpp"

namespace graphics {

	ConnectionScreen_Button::ConnectionScreen_Button(ConnectionScreen* view) : m_view(view)  {

	}

	void ConnectionScreen_Button::enter(void* origin) {
		m_view->startConnection();
	}

	void ConnectionScreen_Button::pressed() {
		m_view->startConnection();
	}
}


