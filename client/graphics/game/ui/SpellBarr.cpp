/*
 * SpellBarr.cpp
 *
 *  Created on: 24 avr. 2013
 *      Author: Béni
 */

#include "SpellBarr.h"
#include "../../inheritedListener/SpellBar_Button.hpp"

namespace graphics {
	SpellBarr::SpellBarr(game::Player* player) {
		setLayout(&m_layout);
		setBackground("ressources/gui/spellBarr_background.png", none);
		m_width = 0;
		for (int i = 0 ; i < game::SpellList::size() ; i++ ){
			ButtonImage* tmp = new ButtonImage(game::SpellList::get(i)->getImage(), game::SpellList::get(i)->getSubrect(), GUIStyle::buttonImage());
			tmp->setFocusFrame(new FocusFrame(game::SpellList::get(i)->getName(), game::SpellList::get(i)->getContents(), GUIStyle::focusFrame()));
			tmp->addListener(new SpellBar_Button(this));
			add(tmp);
			m_buttons.push_back(tmp);
			m_width += 37;
			m_buttonSpells[tmp] = game::SpellList::get(i);
		}
		m_width += 12;
		m_height = 49;
	}

	SpellBarr::~SpellBarr() {

	}

	void SpellBarr::spellActivate(void* origin) {
		if(m_buttonSpells.find((ButtonImage*)origin) != m_buttonSpells.end()) {
			Cursor::set(CURSOR_GAMEFOCUS);
			game::CurrentSpell::set(m_buttonSpells[(ButtonImage*)origin]);

		}

	}

} /* namespace graphics */
