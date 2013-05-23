/*
 * SpellBarr.cpp
 *
 *  Created on: 24 avr. 2013
 *      Author: Béni
 */

#include "SpellBarr.h"

namespace graphics {
	SpellBarr::SpellBarr(game::Player* player) {
		setLayout(&m_layout);
		setBackground("ressources/gui/spellBarr_background.png", none);
		m_width = 0;
		for (int i = 0 ; i < 4 ; i++ ){
			ButtonImage* tmp = new ButtonImage("ressources/game/icon.png", sf::Rect<int>(i*25,0,25,25), GUIStyle::buttonImage());
			add(tmp);
			m_buttons.push_back(*tmp);
			m_width += 37;
		}
		m_width += 12;
		m_height = 49;
	}

	SpellBarr::~SpellBarr() {
		for(std::vector<ButtonImage>::iterator it = m_buttons.begin() ; it != m_buttons.end() ; ++it) {
			delete &(*it);
		}
	}

	bool SpellBarr::event(sf::Event* event, bool used){return Container::event(event, used);}

} /* namespace graphics */
