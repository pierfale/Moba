/*
 * StringStyle.cpp
 *
 *  Created on: 26 mai 2013
 *      Author: pierre
 */


#include "StringStyle.hpp"

namespace graphics {

	StringStyle::StringStyle() {
		m_color = sf::Color::Black;
		m_size = 12;
		m_bold = false;
		m_italic = false;
		m_underline = false;
	}

	StringStyle* StringStyle::copy() {
		StringStyle* n = new StringStyle();
		n->setColor(m_color);
		n->setSize(m_size);
		n->setBold(m_bold);
		n->setItalic(m_italic);
		n->setUnderline(m_underline);
		return n;
	}

	sf::Color StringStyle::color() {
		return m_color;
	}

	int StringStyle::size() {
		return m_size;
	}

	bool StringStyle::isBold() {
		return m_bold;
	}

	bool StringStyle::isItalic() {
		return m_italic;
	}

	bool StringStyle::isUnderline() {
		return m_underline;
	}


	sf::Uint32 StringStyle::style() {
		return m_bold | (m_italic << 1) | (m_underline << 2);
	}



	void StringStyle::setColor(sf::Color color) {
		m_color = color;
	}

	void StringStyle::setSize(int size) {
		m_size = size;
	}

	void StringStyle::setBold(bool state) {
		m_bold = state;
	}

	void StringStyle::setItalic(bool state) {
		m_italic = state;
	}

	void StringStyle::setUnderline(bool state) {
		m_underline = state;
	}

}



