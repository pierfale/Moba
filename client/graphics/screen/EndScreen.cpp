/*
 * EndScreen.cpp
 *
 *  Created on: 23 mai 2013
 *      Author: Béni
 */

#include "EndScreen.h"

namespace graphics {

EndScreen::EndScreen() {
	m_frame = new FrameEndGame();
	m_returnButton = NULL;
	load();
}

EndScreen::~EndScreen() {
	delete m_returnButton;
	delete m_frame;
}

void EndScreen::load() {
	setBackground("ressources/gui/background1.png", none);

	add(m_frame);
	m_returnButton = new Button("Return", GUIStyle::button());
	m_returnButton->setSize(200, 50);
	add(m_returnButton);

	validate();
}

std::string EndScreen::getComponentName() {
	return "EndScreen";
}

std::string EndScreen::getName() {
	return "EndScreen";
}

Chat* EndScreen::getChat() {
	return NULL;//TODO ok,
}

} /* namespace graphics */
