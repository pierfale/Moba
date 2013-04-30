/*
 * WindowStyle.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#include "WindowStyle.hpp"

namespace graphics {

	WindowStyle::WindowStyle() : m_font(sf::Font::getDefaultFont()), m_fontSize(20), m_fontColor(sf::Color::Black) {
		m_botImage = NULL;
		m_topImage = NULL;
		m_centerImage = NULL;
		m_buttonImage = NULL;
	}

	void WindowStyle::setTopImage(std::string path) {
		m_topImage = ImageLoader::get(path);
		int width = m_topImage->getSize().x;
		int height = m_topImage->getSize().y;

		m_topleft.setTexture(*m_topImage);
		m_topleft.setTextureRect(sf::IntRect(0, 0, (width-1)/2, height));
		m_top.setTexture(*m_topImage);
		m_top.setTextureRect(sf::IntRect((width-1)/2, 0, 1, height));
		m_topright.setTexture(*m_topImage);
		m_topright.setTextureRect(sf::IntRect((width-1)/2+1, 0, (width-1)/2, height));
	}

	void WindowStyle::setBotImage(std::string path) {
		m_botImage = ImageLoader::get(path);
		int width = m_botImage->getSize().x;
		int height = m_botImage->getSize().y;
		m_left.setTexture(*m_botImage);
		m_left.setTextureRect(sf::IntRect(0, 0, (width-1)/2, 1));
		m_right.setTexture(*m_botImage);
		m_right.setTextureRect(sf::IntRect((width-1)/2+1, 0, (width-1)/2, 1));

		m_botleft.setTexture(*m_botImage);
		m_botleft.setTextureRect(sf::IntRect(0, 1, (width-1)/2, height-1));
		m_bot.setTexture(*m_botImage);
		m_bot.setTextureRect(sf::IntRect((width-1)/2, 1, 1,  height-1));
		m_botright.setTexture(*m_botImage);
		m_botright.setTextureRect(sf::IntRect((width-1)/2+1, 1, (width-1)/2, height-1));
	}

	void WindowStyle::setButtonImage(std::string path) {
		m_buttonImage = ImageLoader::get(path);
		int width = m_buttonImage->getSize().x/StateCount;
		int height = m_buttonImage->getSize().y;
		for(int i=0; i<StateCount; i++) {
			m_button[i].setTexture(*m_buttonImage);
			m_button[i].setTextureRect(sf::IntRect(i*width, 0, width,  height));
		}
	}

	void WindowStyle::setCenterImage(std::string path) {
		m_centerImage = ImageLoader::get(path);
		m_center.setTexture(*m_centerImage);
		m_center.setTextureRect(sf::IntRect(0, 0, m_centerImage->getSize().x,  m_centerImage->getSize().y));
	}

	void WindowStyle::setFont(sf::Font font) {
		m_font = font;
	}

	void WindowStyle::setFontSize(int fontSize) {
		m_fontSize = fontSize;
	}

	void WindowStyle::setFontColor(sf::Color color) {
		m_fontColor = color;
	}

	void WindowStyle::setHeaderOffset(util::CoordInt coord) {
		m_headerOffset = coord;
	}

	sf::Sprite* WindowStyle::topleft() {
		return &m_topleft;
	}

	sf::Sprite* WindowStyle::top() {
		return &m_top;
	}

	sf::Sprite* WindowStyle::topright() {
		return &m_topright;
	}

	sf::Sprite* WindowStyle::button(State s) {
		return &m_button[s];
	}

	sf::Sprite* WindowStyle::center() {
		return &m_center;
	}

	sf::Sprite* WindowStyle::botright() {
		return &m_botright;
	}

	sf::Sprite* WindowStyle::bot() {
		return &m_bot;
	}

	sf::Sprite* WindowStyle::botleft() {
		return &m_botleft;
	}

	sf::Sprite* WindowStyle::left() {
		return &m_left;
	}

	sf::Sprite* WindowStyle::right () {
		return &m_right;
	}

	sf::Font* WindowStyle::font() {
		return &m_font;
	}

	int WindowStyle::fontSize() {
		return m_fontSize;
	}

	sf::Color* WindowStyle::fontColor() {
		return &m_fontColor;
	}

	util::CoordInt WindowStyle::headerOffset() {
		return m_headerOffset;
	}

}

