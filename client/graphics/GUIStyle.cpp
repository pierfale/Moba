/*
 * GUIStyle.cpp
 *
 *  Created on: 9 avr. 2013
 *      Author: pierre
 */

#include "GUIStyle.hpp"

namespace graphics {

	boost::shared_ptr<GUIStyle> GUIStyle::m_instance;

	GUIStyle::GUIStyle() {

	}

	GUIStyle::~GUIStyle() {

	}

	void GUIStyle::init() {
		m_instance.reset(new GUIStyle());
		getInstance()->m_button.reset(new BasicStyle());
		getInstance()->m_button.get()->setBorderImage("ressources/gui/button_2.png");
		getInstance()->m_button.get()->setCenterImage("ressources/gui/button_2_center.png");
		getInstance()->m_button.get()->setFontColor(sf::Color(226, 233, 40));

		getInstance()->m_textfield.reset(new BasicStyle());
		getInstance()->m_textfield.get()->setBorderImage("ressources/gui/textfield_2.png");
		getInstance()->m_textfield.get()->setCenterImage("ressources/gui/textfield_center.png");

		getInstance()->m_label.reset(new BasicStyle());

		getInstance()->m_innerwindow.reset(new WindowStyle());
		getInstance()->m_innerwindow.get()->setBotImage("ressources/gui/window_bot.png");
		getInstance()->m_innerwindow.get()->setTopImage("ressources/gui/window_top.png");
		getInstance()->m_innerwindow.get()->setCenterImage("ressources/gui/window_center.png");
		getInstance()->m_innerwindow.get()->setButtonImage("ressources/gui/window_close.png");
		getInstance()->m_innerwindow.get()->setHeaderOffset(util::Coordinates(10, 5));
		getInstance()->m_innerwindow.get()->setFontColor(sf::Color(226, 233, 40));
		getInstance()->m_innerwindow.get()->setFontSize(18);

		getInstance()->m_line.reset(new LineStyle());
		getInstance()->m_line.get()->setLineImage("ressources/gui/line.png");

		getInstance()->m_table.reset(new TableStyle());
		getInstance()->m_table.get()->setBorderSize(0);
		getInstance()->m_table.get()->setHeaderTextColor(sf::Color::White);
		getInstance()->m_table.get()->setHeaderBackgroundColor(sf::Color(30, 30, 30));
		getInstance()->m_table.get()->setTextColor(sf::Color::White);
		getInstance()->m_table.get()->setBackgroundColorFocus(sf::Color(200, 200, 200, 150));
		getInstance()->m_table.get()->setBackgroundColorSelect(sf::Color(150, 150, 150, 150));

		getInstance()->m_characterFrame.reset(new BasicStyle());
		getInstance()->m_characterFrame.get()->setBorderImage("ressources/gui/button_character.png");
		getInstance()->m_characterFrame.get()->setCenterImage("ressources/gui/button_character_center.png");
		getInstance()->m_characterFrame.get()->setFontColor(sf::Color(255,255,255));

		getInstance()->m_buttonImage.reset(new BasicStyle());
		getInstance()->m_buttonImage.get()->setBorderImage("ressources/gui/button_image.png");
		getInstance()->m_buttonImage.get()->setCenterImage("ressources/gui/button_imagecenter.png");
		getInstance()->m_buttonImage.get()->setFontColor(sf::Color(226, 233, 40));

	}

	BasicStyle* GUIStyle::button() {
		return getInstance()->m_button.get();
	}

	BasicStyle* GUIStyle::label() {
		return getInstance()->m_label.get();
	}

	BasicStyle* GUIStyle::textfield() {
		return getInstance()->m_textfield.get();
	}

	WindowStyle* GUIStyle::innerwindow() {
		return getInstance()->m_innerwindow.get();
	}

	LineStyle* GUIStyle::line() {
		return getInstance()->m_line.get();
	}

	TableStyle* GUIStyle::table() {
		return getInstance()->m_table.get();
	}

	BasicStyle* GUIStyle::characterFrame() {
		return getInstance()->m_characterFrame.get();
	}

	BasicStyle* GUIStyle::buttonImage() {
		return getInstance()->m_buttonImage.get();
	}

	GUIStyle* GUIStyle::getInstance() {
		if(m_instance.get() == NULL)
			log_err "GUIStyle need to be init" end_log_err;
		return m_instance.get();
	}
}


