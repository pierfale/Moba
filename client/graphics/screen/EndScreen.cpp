/*
 * EndScreen.cpp
 *
 *  Created on: 23 mai 2013
 *      Author: Béni
 */

#include "EndScreen.h"

namespace graphics {

EndScreen::EndScreen() {
	Cursor::set(CURSOR_NONE);
	setLayout(new PassivLayout());

	m_frame = new FrameEndGame();
	m_exp = new FrameExp();
	m_returnButton = NULL;
	load();
}

EndScreen::~EndScreen() {
	delete m_returnButton;
//	delete m_frame;
	delete m_exp;
	delete m_chat;
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

void EndScreen::load() {
	setBackground("ressources/gui/background1.png", full);

	m_leftContainer.add(m_frame);
	m_leftContainer.setLayout(new VerticalLayout());

	m_chat = new Chat();
	game::ChatList::add(m_chat);

	m_returnButton = new Button("Return", GUIStyle::button());
	m_returnButton->setSize(200, 50);
	m_returnButton->addListener(new EndScreenListner_Button());
	m_buttonContainer.setLayout(new PassivLayout());
	m_buttonContainer.add(m_returnButton);

	m_rightBottomContainer.add(m_chat);
	m_rightBottomContainer.add(&m_buttonContainer);
	m_rightBottomContainer.setLayout(new SplitFixedLayout(SplitFixedLayout::horizontal, SplitFixedLayout::second, 50));

	m_containerExp.add(m_exp);
	m_rightContainer.add(&m_containerExp);
	m_rightContainer.add(&m_rightBottomContainer);
	m_rightContainer.setLayout(new SplitFixedLayout(SplitFixedLayout::horizontal, SplitFixedLayout::first , 64));

	add(&m_leftContainer);
	add(&m_rightContainer);
	this->setLayout(new SplitFixedLayout(SplitFixedLayout::vertical, SplitFixedLayout::second, 300));

}

} /* namespace graphics */
