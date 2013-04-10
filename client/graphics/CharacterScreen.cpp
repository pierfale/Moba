/*
 * CharacterScreen.cpp
 *
 *  Created on: 9 avr. 2013
 *      Author: pierre
 */

#include "CharacterScreen.hpp"

namespace graphics {

	CharacterScreen::CharacterScreen(Window* window) : m_window(window) {

	}

	void CharacterScreen::load() {
		Container* containerChar = new Container();
		this->add(containerChar);
		containerChar->setBackground("ressources/gui/background1.png", full);

		Container* containerInfo = new Container();
		this->add(containerInfo);

		this->setLayout(new SplitFixedLayout(SplitFixedLayout::vertical, SplitFixedLayout::first, 250));
		std::cout << ">>" << containerChar->toString() << std::endl;

	}
}


