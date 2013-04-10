/*
 * CharacterScreen.cpp
 *
 *  Created on: 9 avr. 2013
 *      Author: pierre
 */

#include "CharacterScreen.hpp"

namespace graphics {

	CharacterScreen::CharacterScreen(Window* window) : m_window(window) {

		Container* containerChar = new Container();
		containerChar->setBackground("ressources/gui/background1.png", full);
		this->add(containerChar);

		Container* containerInfo = new Container();
		this->add(containerInfo);

		this->setLayout(new SplitFixedLayout(SplitFixedLayout::vertical, SplitFixedLayout::first, 250));

	}
}


