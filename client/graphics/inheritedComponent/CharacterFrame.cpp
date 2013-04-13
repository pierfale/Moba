/*
 * CharacterFrame.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#include "CharacterFrame.hpp"

namespace graphics {

	CharacterFrame::CharacterFrame(game::Player* player) : Button(""), m_player(player), m_select(false) {
		m_height = 45;
	}

	void CharacterFrame::setSelect(bool state) {
		m_select = state;
	}

	bool CharacterFrame::isSelectable() {
		return false;
	}

	game::Player* CharacterFrame::getPlayer() {
		return m_player;
	}

	void CharacterFrame::draw(sf::RenderWindow* render) {
		util::Coordinates coord = getRealCoord();
		int border = 1;
		sf::RectangleShape background(sf::Vector2f(m_width-2*border, m_height-2*border));

		background.setPosition(sf::Vector2f(coord.x+border, coord.y+border));

		if(m_focus)
			background.setFillColor(sf::Color(100, 100, 100, 150));
		else
			background.setFillColor(sf::Color(80, 80, 80, 150));

		background.setOutlineThickness(border);
		if(m_select)
			background.setOutlineColor(sf::Color::Red);
		else
			background.setOutlineColor(sf::Color::Black);
		render->draw(background);

		sf::Text name(m_player->getName());
		name.setCharacterSize(18);
		name.setColor(sf::Color::White);
		sf::FloatRect textSize = name.getGlobalBounds();
		name.setPosition(coord.x+5,coord.y);
		render->draw(name);

		sf::Text level("level "+util::Cast::intToString(m_player->getLevel()));
		level.setCharacterSize(14);
		level.setColor(sf::Color::White);
		textSize = level.getGlobalBounds();
		level.setPosition(coord.x+5,coord.y+25);
		render->draw(level);

	}

}


