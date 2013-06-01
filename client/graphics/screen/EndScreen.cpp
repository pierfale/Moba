/*
 * EndScreen.cpp
 *
 *  Created on: 23 mai 2013
 *      Author: Béni
 */

#include "EndScreen.h"

namespace graphics {

EndScreen::EndScreen() {

	setLayout(new PassivLayout());

	m_frame = new FrameEndGame();
	m_returnButton = NULL;
	load();
}

EndScreen::~EndScreen() {
	delete m_returnButton;
	delete m_frame;
}

void EndScreen::load() {
	setBackground("ressources/gui/background1.png", full);
	this->setLayout(new SplitFixedLayout(SplitFixedLayout::vertical, SplitFixedLayout::second, 300));

	m_leftContainer.add(m_frame);
	m_leftContainer.setLayout(new VerticalLayout());

	m_chat = new Chat();
	game::ChatList::add(m_chat);

	m_returnButton = new Button("Return", GUIStyle::button());
	m_returnButton->setSize(200, 50);
	m_returnButton->addListener(new EndScreenListner_Button());
	m_buttonContainer.add(m_returnButton);

	m_rightContainer.add(m_chat);
	m_rightContainer.setLayout(new SplitFixedLayout(SplitFixedLayout::horizontal, SplitFixedLayout::second, 50));
	m_rightContainer.add(&m_buttonContainer);

	add(&m_leftContainer);
	add(&m_rightContainer);

}

} /* namespace graphics */
