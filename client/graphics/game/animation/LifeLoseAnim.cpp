/*
 * LifeLoseAnim.cpp
 *
 *  Created on: 5 juin 2013
 *      Author: pierre
 */

#include "LifeLoseAnim.hpp"

namespace graphics {

	LifeLoseAnim::LifeLoseAnim(bool isPhysical, int n, game::Player* player) : m_player(player) {
		m_text.setString(util::Cast::intToString(n));
		if(isPhysical)
			m_text.setColor(sf::Color::Red);
		else
			m_text.setColor(sf::Color::Blue);
		m_text.setCharacterSize(16);
		m_y = 0;
		m_first = true;
	}

	int LifeLoseAnim::getValueY() {
		return m_player->getCoord().y;
	}

	void LifeLoseAnim::draw(sf::RenderWindow* render, Camera* cam) {

		if(m_first) {
			m_timer.restart();
			m_first = false;
		}

		m_y += m_timer.elapsed()*20;

		m_timer.restart();

		if(m_y > 30.0)
			m_done = true;

		m_text.setPosition(m_player->getCoord().x-m_text.getGlobalBounds().width/2-cam->getCoord().x, m_player->getCoord().y-100-m_text.getCharacterSize()-m_y-cam->getCoord().y);
		render->draw(m_text);
	}
}


