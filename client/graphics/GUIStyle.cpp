/*
 * GUIStyle.cpp
 *
 *  Created on: 9 avr. 2013
 *      Author: pierre
 */

#include "GUIStyle.hpp"

namespace graphics {

	GUIStyle* GUIStyle::m_instance = NULL;

	GUIStyle::GUIStyle() {
		m_button = NULL;
		m_textfield = NULL;
		m_label = NULL;
		m_innerwindow = NULL;
	}

	void GUIStyle::init(Window* window) {
		m_instance = new GUIStyle();
		getInstance()->m_button = new BasicStyle(window);
		getInstance()->m_button->setBorderImage("ressources/gui/button_2.png");
		getInstance()->m_button->setCenterImage("ressources/gui/button_2_center.png");
		getInstance()->m_button->setFontColor(sf::Color(226, 233, 40));

		getInstance()->m_textfield = new BasicStyle(window);
		getInstance()->m_textfield->setBorderImage("ressources/gui/textfield_2.png");
		getInstance()->m_textfield->setCenterImage("ressources/gui/textfield_center.png");

		getInstance()->m_label = new BasicStyle(window);

		getInstance()->m_innerwindow = new WindowStyle(window);
		getInstance()->m_innerwindow->setBotImage("ressources/gui/window_bot.png");
		getInstance()->m_innerwindow->setTopImage("ressources/gui/window_top.png");
		getInstance()->m_innerwindow->setCenterImage("ressources/gui/window_center.png");
		getInstance()->m_innerwindow->setButtonImage("ressources/gui/window_close.png");
		getInstance()->m_innerwindow->setHeaderOffset(util::Coordinates(10, 5));
		getInstance()->m_innerwindow->setFontColor(sf::Color(226, 233, 40));
		getInstance()->m_innerwindow->setFontSize(18);
	}

	BasicStyle* GUIStyle::button() {
		return getInstance()->m_button;
	}

	BasicStyle* GUIStyle::label() {
		return getInstance()->m_label;
	}

	BasicStyle* GUIStyle::textfield() {
		return getInstance()->m_textfield;
	}

	WindowStyle* GUIStyle::innerwindow() {
		return getInstance()->m_innerwindow;
	}

	GUIStyle* GUIStyle::getInstance() {
		if(m_instance == NULL)
			client::Log::err("GUIStyle need to be init");
		return m_instance;
	}
}


