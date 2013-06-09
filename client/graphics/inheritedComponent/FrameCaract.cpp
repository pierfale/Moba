/*
 * FrameCaract.cpp
 *
 *  Created on: 5 juin 2013
 *      Author: Béni
 */

#include "FrameCaract.h"

namespace graphics {

FrameCaract::FrameCaract(game::Character* chara) {
	m_char = chara;
	m_font.loadFromFile("ressources/gui/font.ttf");
	m_textureBackground = ImageLoader::get("ressources/gui/playerInfo_background.png");
	m_textureIcon = ImageLoader::get("ressources/game/icon.png");
}
FrameCaract::~FrameCaract() {}


void FrameCaract::draw(sf::RenderWindow* render) {
	if (getParent() == NULL) return;

	sf::Sprite sprite;
	sf::Text text;
	sprite.setTexture(*m_textureBackground);
	sprite.setPosition(m_coord.x , m_coord.y-(45*0.8181));
	sprite.setScale(1.0,0.8181);
	render->draw(sprite);

	text.setColor(sf::Color::White);
	text.setCharacterSize(8);
	sprite.setTexture(*m_textureIcon);
	sprite.setScale(0.5,0.5);

	sprite.setTextureRect(sf::IntRect(0,0,25,25));
	sprite.setPosition(m_coord.x + 15,m_coord.y-(40*0.8181));
	render->draw(sprite);
	text.setString(util::Cast::intToString(m_char->getStat()->physicalAttack()));
	text.setPosition( m_coord.x + 30,m_coord.y-(37*0.8181));
	render->draw(text);

	sprite.setTextureRect(sf::IntRect(25,0,25,25));
	sprite.setPosition( m_coord.x + 15,m_coord.y-(20*0.8181));
	render->draw(sprite);
	text.setString(util::Cast::intToString(m_char->getStat()->magicalAttack()));
	text.setPosition(  m_coord.x + 30, m_coord.y-(17*0.8181));
	render->draw(text);

	sprite.setTextureRect(sf::IntRect(50,0,25,25));
	sprite.setPosition(m_coord.x + 45, m_coord.y-(40*0.8181));
	render->draw(sprite);
	text.setString(util::Cast::intToString(m_char->getStat()->attackSpeed()));
	text.setPosition( m_coord.x + 60,m_coord.y-(37*0.8181));
	render->draw(text);

	sprite.setTextureRect(sf::IntRect(75,0,25,25));
	sprite.setPosition(m_coord.x + 45, m_coord.y-(20*0.8181));
	render->draw(sprite);
	text.setString(util::Cast::intToString(m_char->getStat()->movementSpeed()));
	text.setPosition(  m_coord.x + 60, m_coord.y-(17*0.8181));
	render->draw(text);

	sprite.setTextureRect(sf::IntRect(100,0,25,25));
	sprite.setPosition(m_coord.x + 75, m_coord.y-(40*0.8181));
	render->draw(sprite);
	text.setString(util::Cast::intToString(m_char->getStat()->physicalArmor()));
	text.setPosition(m_coord.x + 90, m_coord.y-(37*0.8181));
	render->draw(text);

	sprite.setTextureRect(sf::IntRect(125,0,25,25));
	sprite.setPosition( m_coord.x + 75, m_coord.y-(20*0.8181));
	render->draw(sprite);
	text.setString(util::Cast::intToString(m_char->getStat()->magicalArmor()));
	text.setPosition(m_coord.x + 90, m_coord.y-(17*0.8181));
	render->draw(text);

	sprite.setTextureRect(sf::IntRect(150,0,25,25));
	sprite.setPosition( m_coord.x + 105, m_coord.y-(40*0.8181));
	render->draw(sprite);
	text.setString(util::Cast::intToString(m_char->getStat()->range()));
	text.setPosition( m_coord.x + 120, m_coord.y-(37*0.8181));
	render->draw(text);

	sprite.setTextureRect(sf::IntRect(175,0,25,25));
	sprite.setPosition( m_coord.x + 105, m_coord.y-(20*0.8181));
	render->draw(sprite);
	text.setString(util::Cast::intToString(m_char->getStat()->movementSpeed())); //TODO get Money
	text.setPosition( m_coord.x + 120, m_coord.y-(17*0.8181));
	render->draw(text);
}

bool FrameCaract::event(sf::Event* event, bool used) {
	return used;
}

} /* namespace graphics */
