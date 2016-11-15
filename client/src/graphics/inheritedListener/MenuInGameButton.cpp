/*
 * MenuInGameButton.cpp
 *
 *  Created on: 4 mai 2013
 *      Author: Béni
 */

#include "MenuInGameButton.h"
#include "../game/ui/UserInterface.h"

namespace graphics {

MenuInGame_Button::MenuInGame_Button(UserInterface* interface) {m_interface = interface;}
MenuInGame_Button::~MenuInGame_Button() {}

void MenuInGame_Button::pressed(void* origin) {
	if (((Button*)origin)->getText().compare("Quit") == 0) {
		m_interface->confirm();
	} else if (((Button*)origin)->getText().compare("No") == 0) {
		m_interface->removeConfirm();
	} else if (((Button*)origin)->getText().compare("Yes") == 0) {
		m_interface->quit();
	}
}


} /* namespace graphics */
