/*
 * Chat_Listener.cpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#include "Chat_Listener.hpp"

namespace graphics {

	Chat_ButtonListener::Chat_ButtonListener(Chat* view) : m_view(view) {

	}

	void Chat_ButtonListener::pressed(void* origin) {
		m_view->send(origin);
	}

	void Chat_ButtonListener::enter(void* origin) {
		m_view->send(origin);
	}

	Chat_TextFieldListener::Chat_TextFieldListener(Chat* view) : m_view(view) {

	}

	void Chat_TextFieldListener::enter(void* origin) {
		m_view->send(origin);
	}

}


