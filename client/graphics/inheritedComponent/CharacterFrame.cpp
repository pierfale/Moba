/*
 * CharacterFrame.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#include "CharacterFrame.hpp"

namespace graphics {

	CharacterFrame::CharacterFrame(game::Player* player) : Button(""), m_player(player), m_select(false) {
		m_height = 55;
		m_style = new BasicStyle();
		m_style->setBorderImage("ressources/gui/button_character.png");
		m_style->setCenterImage("ressources/gui/button_character_center.png");
		m_style->setFontColor(sf::Color(255,255,255));
	}

	void CharacterFrame::setSelect(bool state, bool force) {
		m_select = state;
	}

	bool CharacterFrame::isSelectable() {
		return false;
	}

	game::Player* CharacterFrame::getPlayer() {
		return m_player;
	}

	void CharacterFrame::draw(sf::RenderWindow* render) {
		util::CoordInt coord = getRealCoord();
		if(m_select)
			m_selected = true;

		m_width -= 10;
		m_height -= 4;
		m_coord.x += 5;
		m_coord.y += 2;

		Button::draw(render);

		m_width += 10;
		m_height += 4;
		m_coord.x -= 5;
		m_coord.y -= 2;

		m_selected = false;
		sf::Text name(m_player->getName());
		name.setCharacterSize(18);
		name.setColor(sf::Color::White);
		sf::FloatRect textSize = name.getGlobalBounds();
		name.setPosition(coord.x+13,coord.y+5);
		render->draw(name);

		sf::Text level("level "+util::Cast::intToString(m_player->getLevel()));
		level.setCharacterSize(14);
		level.setColor(sf::Color::White);
		textSize = level.getGlobalBounds();
		level.setPosition(coord.x+13,coord.y+30);
		render->draw(level);

	}

}


