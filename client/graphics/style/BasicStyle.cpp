/*
 * BasicStyle.cpp
 *
 *  Created on: 7 avr. 2013
 *      Author: pierre
 */

#include "BasicStyle.hpp"

namespace graphics {

	BasicStyle::BasicStyle(Window* window) : m_window(window), m_font(sf::Font::getDefaultFont()), m_fontSize(20), m_fontColor(sf::Color::Black) {
		m_borderImage = NULL;
		m_centerImage = NULL;
	}

	void BasicStyle::setBorderImage(std::string path) {
		m_window->getImageLoader()->add(path);
		m_borderImage = m_window->getImageLoader()->get(path);
		int width = m_borderImage->getSize().x/StateCount;
		int height = m_borderImage->getSize().y;
		for(int i=0; i<StateCount; i++) {
			m_topleft[i].setTexture(*m_borderImage);
			m_topleft[i].setTextureRect(sf::IntRect(i*width, 0, (width-1)/2, (height-1)/2));
			m_top[i].setTexture(*m_borderImage);
			m_top[i].setTextureRect(sf::IntRect(i*width+(width-1)/2, 0, 1, (height-1)/2));
			m_topright[i].setTexture(*m_borderImage);
			m_topright[i].setTextureRect(sf::IntRect(i*width+(width-1)/2+1, 0, (width-1)/2, (height-1)/2));
			m_right[i].setTexture(*m_borderImage);
			m_right[i].setTextureRect(sf::IntRect(i*width+(width-1)/2+1, (height-1)/2, (width-1)/2, 1));
			m_botright[i].setTexture(*m_borderImage);
			m_botright[i].setTextureRect(sf::IntRect(i*width+(width-1)/2+1, (height-1)/2+1, (width-1)/2, (height-1)/2));
			m_bot[i].setTexture(*m_borderImage);
			m_bot[i].setTextureRect(sf::IntRect(i*width+(width-1)/2, (height-1)/2+1, 1, (height-1)/2));
			m_botleft[i].setTexture(*m_borderImage);
			m_botleft[i].setTextureRect(sf::IntRect(i*width, (height-1)/2+1, (width-1)/2, (height-1)/2));
			m_left[i].setTexture(*m_borderImage);
			m_left[i].setTextureRect(sf::IntRect(i*width, (height-1)/2, (width-1)/2, 1));
		}
	}

	void BasicStyle::setCenterImage(std::string path) {
		m_window->getImageLoader()->add(path);
		m_centerImage = m_window->getImageLoader()->get(path);
		for(int i=0; i<StateCount; i++) {
			m_center[i].setTexture(*m_centerImage);
			m_center[i].setTextureRect(sf::IntRect(i*(m_centerImage->getSize().x/4), 0, m_centerImage->getSize().x/4, m_centerImage->getSize().y));
		}

	}

	void BasicStyle::setFont(sf::Font font) {
		m_font = font;
	}

	void BasicStyle::setFontSize(int fontSize) {
		m_fontSize = fontSize;
	}

	void BasicStyle::setFontColor(sf::Color color) {
		m_fontColor = color;
	}

	sf::Sprite* BasicStyle::center(State s) {
		return &m_center[s];
	}

	sf::Sprite* BasicStyle::topleft(State s) {
		return &m_topleft[s];
	}

	sf::Sprite* BasicStyle::top(State s) {
		return &m_top[s];
	}

	sf::Sprite* BasicStyle::topright(State s) {
		return &m_topright[s];
	}

	sf::Sprite* BasicStyle::right(State s) {
		return &m_right[s];
	}

	sf::Sprite* BasicStyle::botright(State s) {
		return &m_botright[s];
	}

	sf::Sprite* BasicStyle::bot(State s) {
		return &m_bot[s];
	}

	sf::Sprite* BasicStyle::botleft(State s) {
		return &m_botleft[s];
	}

	sf::Sprite* BasicStyle::left(State s) {
		return &m_left[s];
	}

	sf::Font* BasicStyle::font() {
		return &m_font;
	}

	int BasicStyle::fontSize() {
		return m_fontSize;
	}

	sf::Color* BasicStyle::fontColor() {
		return &m_fontColor;
	}
}


