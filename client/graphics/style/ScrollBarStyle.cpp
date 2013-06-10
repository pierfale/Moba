/*
 * ScrollBarStyle.cpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#include "ScrollBarStyle.hpp"

namespace graphics {

	void ScrollBarStyle::setBackgroundImage(std::string path) {
		m_backgroundImage = ImageLoader::get(path);

		m_backgroundTop.setTexture(*m_backgroundImage);
		m_backgroundTop.setTextureRect(sf::IntRect(0, 0, m_backgroundImage->getSize().x, (m_backgroundImage->getSize().y-1)/2));

		m_backgroundCenter.setTexture(*m_backgroundImage);
		m_backgroundCenter.setTextureRect(sf::IntRect(0, (m_backgroundImage->getSize().y-1)/2, m_backgroundImage->getSize().x, 1));

		m_backgroundBot.setTexture(*m_backgroundImage);
		m_backgroundBot.setTextureRect(sf::IntRect(0, (m_backgroundImage->getSize().y-1)/2+1, m_backgroundImage->getSize().x, (m_backgroundImage->getSize().y-1)/2));
	}

	void ScrollBarStyle::setBarImage(std::string path) {
		m_barImage = ImageLoader::get(path);

		m_barTop.setTexture(*m_barImage);
		m_barTop.setTextureRect(sf::IntRect(0, 0, m_barImage->getSize().x, (m_barImage->getSize().y-1)/2));

		m_barCenter.setTexture(*m_barImage);
		m_barCenter.setTextureRect(sf::IntRect(0, (m_barImage->getSize().y-1)/2, m_barImage->getSize().x, 1));

		m_barBot.setTexture(*m_barImage);
		m_barBot.setTextureRect(sf::IntRect(0, (m_barImage->getSize().y-1)/2+1, m_barImage->getSize().x, (m_barImage->getSize().y-1)/2));
	}

	sf::Sprite* ScrollBarStyle::backgroundTop() {
		return &m_backgroundTop;
	}

	sf::Sprite* ScrollBarStyle::backgroundCenter() {
		return &m_backgroundCenter;
	}

	sf::Sprite* ScrollBarStyle::backgroundBot() {
		return &m_backgroundBot;
	}

	sf::Sprite* ScrollBarStyle::barTop() {
		return &m_barTop;
	}

	sf::Sprite* ScrollBarStyle::barCenter() {
		return &m_barCenter;
	}

	sf::Sprite* ScrollBarStyle::barBot() {
		return &m_barBot;
	}

}


