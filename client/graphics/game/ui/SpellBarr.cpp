/*
 * SpellBarr.cpp
 *
 *  Created on: 24 avr. 2013
 *      Author: Béni
 */

#include "SpellBarr.h"

namespace graphics {
	SpellBarr::SpellBarr(game::Player* player) {
		for (int i = 0 ; i < 3 ; i++) {
			ButtonImage* tmp = new ButtonImage("ressouces/game/icon.png", sf::Rect<int>(i*25,0,25,25), GUIStyle::buttonImage());
			m_buttons.push_back(*tmp);
			add(tmp);
		}
		m_layout.setContainer(this);
	}

	SpellBarr::~SpellBarr() {
		for(std::vector<ButtonImage>::iterator it = m_buttons.begin() ; it != m_buttons.end() ; ++it) {
			delete &(*it);
		}
	}

	bool SpellBarr::event(sf::Event* event, bool used){return used;}

} /* namespace graphics */
