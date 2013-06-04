/*
 * FrameExp.cpp
 *
 *  Created on: 1 juin 2013
 *      Author: Béni
 */

#include "FrameExp.h"

namespace graphics {

FrameExp::FrameExp() {
	m_font.loadFromFile("ressources/gui/font.ttf");
	m_texture = ImageLoader::get("ressources/gui/playerInfo_background.png");
	m_expFinal = game::CurrentCharacter::get()->getExp() + game::CurrentCharacter::get()->getExpEarned();
	m_timer.restart();
}

void FrameExp::draw(sf::RenderWindow* render) {
	util::CoordInt coord = getRealCoord();
	int offset;
	int expCurr = game::CurrentCharacter::get()->getExp();
	if (m_timer.elapsed() > 0.95) {
		if (expCurr != m_expFinal) {
			game::CurrentCharacter::get()->incExp();
			expCurr = game::CurrentCharacter::get()->getExp();
		}
	}
	int expReq = game::CurrentCharacter::get()->getExpRequired();
	int expEarned = game::CurrentCharacter::get()->getExpEarned();
	int expBar = ( (expCurr * 100) / game::CurrentCharacter::get()->getExpRequired());
	sf::Sprite sprite;
	sf::Text label;

	sprite.setTexture(*m_texture);
	sprite.setScale(1.1,1.3);
	sprite.setPosition(coord.x, coord.y);
	render->draw(sprite);

	label.setFont(m_font);
	label.setCharacterSize(13);

	label.setString(game::CurrentCharacter::get()->getName() + " LvL " + util::Cast::intToString(game::CurrentCharacter::get()->getLevel()));
	label.setPosition(coord.x+5,coord.y+5);
	offset = label.getGlobalBounds().width;
	render->draw(label);

	label.setString(" "+ util::Cast::intToString(expCurr) +"/"+ util::Cast::intToString(expReq));
	label.setPosition(coord.x+offset+5, coord.y+5);
	render->draw(label);

	sf::RectangleShape exp_max;
	exp_max.setSize(sf::Vector2f(100,10));
	exp_max.setOutlineColor(sf::Color(125,125,125));
	exp_max.setOutlineThickness(1.0);
	exp_max.setFillColor(sf::Color::Transparent);
	exp_max.setPosition( coord.x+20, coord.y+25);
	render->draw(exp_max);

	label.setString("+"+ util::Cast::intToString(expEarned)+"EXP");
	label.setPosition( coord.x+20, coord.y+40);
	render->draw(label);

	sf::RectangleShape exp_curr;
	exp_curr.setSize(sf::Vector2f(expBar,10)); //TODO get the EXP of CurrentCharacter with %
	exp_curr.setFillColor(sf::Color(175,175,175));
	exp_curr.setPosition( coord.x+20,  coord.y+25);
	render->draw(exp_curr);
}

bool FrameExp::event(sf::Event* event, bool used) {return used;}

} /* namespace graphics */
