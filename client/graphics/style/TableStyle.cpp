/*
 * TableStyle.cpp
 *
 *  Created on: 18 avr. 2013
 *      Author: pierre
 */

#include "TableStyle.hpp"

namespace graphics {

	TableStyle::TableStyle() {
		m_headerBackgroundColor = sf::Color::Transparent;
		m_headerTextColor = sf::Color::Black;
		m_backgroundColor = sf::Color::Transparent;
		m_textColor = sf::Color::Black;
		m_backgroundColorFocus = sf::Color::Transparent;
		m_backgroundColorSelect = sf::Color::Transparent;
		m_borderSize = 1;
		m_borderColor = sf::Color::Black;
	}

	void TableStyle::setHeaderBackgroundColor(sf::Color color) {
		m_headerBackgroundColor = color;
	}

	void TableStyle::setHeaderTextColor(sf::Color color) {
		m_headerTextColor = color;
	}

	void TableStyle::setBackgroundColor(sf::Color color) {
		m_backgroundColor = color;
	}

	void TableStyle::setTextColor(sf::Color color) {
		m_textColor = color;
	}

	void TableStyle::setBackgroundColorFocus(sf::Color color) {
		m_backgroundColorFocus = color;
	}

	void TableStyle::setBackgroundColorSelect(sf::Color color) {
		m_backgroundColorSelect = color;
	}

	void TableStyle::setBorderSize(int i) {
		m_borderSize = i;
	}

	void TableStyle::setBorderColor(sf::Color color) {
		m_borderColor = color;
	}

	sf::Color TableStyle::headerBackgroundColor() {
		return m_headerBackgroundColor;
	}

	sf::Color TableStyle::headerTextColor() {
		return m_headerTextColor;
	}

	sf::Color TableStyle::backgroundColor() {
		return m_backgroundColor;
	}

	sf::Color TableStyle::textColor() {
		return m_textColor;
	}

	sf::Color TableStyle::backgroundColorFocus() {
		return m_backgroundColorFocus;
	}

	sf::Color TableStyle::backgroundColorSelect() {
		return m_backgroundColorSelect;
	}


	int TableStyle::borderSize() {
		return m_borderSize;
	}

	sf::Color TableStyle::borderColor() {
		return m_borderColor;
	}

}

