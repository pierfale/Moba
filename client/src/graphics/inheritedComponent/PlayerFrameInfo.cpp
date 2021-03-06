/*
 * PlayerFrameInfo.cpp
 *
 *  Created on: 2 mai 2013
 *      Author: B�ni
 */

#include "PlayerFrameInfo.h"
#include "../../game/menu/CurrentCharacter.hpp"

namespace graphics {

PlayerFrameInfo::PlayerFrameInfo() {
	m_char = NULL;
	m_font.loadFromFile("ressources/gui/font.ttf");
	m_textureBackground = ImageLoader::get("ressources/gui/playerInfo_background.png");
	m_textureIcon = ImageLoader::get("ressources/game/icon.png");
	m_scale = 1.0;
	m_offsetX = 0;
	m_offsetY = 0;
}


PlayerFrameInfo::PlayerFrameInfo(game::Character* chara) {
	m_char = chara;
	m_font.loadFromFile("ressources/gui/font.ttf");
	m_textureBackground = ImageLoader::get("ressources/gui/playerInfo_background.png");
	m_textureIcon = ImageLoader::get("ressources/game/icon.png");
	m_scale = 1.0;
	m_offsetX = 0;
	m_offsetY = 0;
}

void PlayerFrameInfo::setPlayer(game::Character* chara){
	m_char = chara;
}

void PlayerFrameInfo::setScale(float scale) {
	m_scale = scale;
}

void PlayerFrameInfo::draw(sf::RenderWindow* render) {
	sf::Sprite sprite;
		if (m_char->getFaction() != game::CurrentCharacter::get()->getFaction() ||
				m_char->getFaction() == network::PacketType::FACTION_AGGRESSIVE)
			sprite.setColor(sf::Color(255,200,200));
		else if (m_char->getFaction() == network::PacketType::FACTION_PEACEFUL)
			sprite.setColor(sf::Color(200,255,200));
		sprite.setTexture(*m_textureBackground);
		sprite.setPosition(m_coord.x,m_coord.y);
		sprite.setScale(m_scale, m_scale);
		render->draw(sprite);

		sf::Text name;
		name.setString(m_char->getName());
		name.setColor(sf::Color::White);
		name.setCharacterSize(13);
		name.setFont(m_font);
		name.setPosition(m_coord.x+((140*m_scale)-name.getGlobalBounds().width)/2,m_coord.y);
		name.setScale(m_scale, m_scale);
		render->draw(name);

		sf::Text hp_label;
		hp_label.setString("HP ");
		hp_label.setColor(sf::Color(230,15,15));
		hp_label.setCharacterSize(15);
		hp_label.setPosition(m_coord.x+10*m_scale,10*m_scale+m_coord.y);
		hp_label.setFont(m_font);
		hp_label.setScale(m_scale, m_scale);
		render->draw(hp_label);

		sf::RectangleShape hp_barr_max;
		hp_barr_max.setSize(sf::Vector2f(100,10));
		hp_barr_max.setOutlineColor(sf::Color(190,25,25));
		hp_barr_max.setOutlineThickness(1.0);
		hp_barr_max.setFillColor(sf::Color::Transparent);
		hp_barr_max.setPosition(30*m_scale+m_coord.x,m_coord.y+14*m_scale);
		hp_barr_max.setScale(m_scale, m_scale);
		render->draw(hp_barr_max);

		sf::RectangleShape hp_barr;
		hp_barr.setSize(sf::Vector2f(((float)m_char->getStat()->life()/(float)m_char->getStat()->maxLife())*100,10));
		hp_barr.setFillColor(sf::Color::Red);
		hp_barr.setPosition(30*m_scale+m_coord.x,m_coord.y+14*m_scale);
		hp_barr.setScale(m_scale, m_scale);
		render->draw(hp_barr);

		sf::Text mp_label;
		mp_label.setString("MP ");
		mp_label.setColor(sf::Color(15,15,230));
		mp_label.setCharacterSize(15);
		mp_label.setFont(m_font);
		mp_label.setPosition(m_coord.x+10*m_scale,m_coord.y+25*m_scale);
		mp_label.setScale(m_scale, m_scale);
		render->draw(mp_label);

		sf::RectangleShape mp_barr_max;
		mp_barr_max.setSize(sf::Vector2f(100,10));
		mp_barr_max.setOutlineColor(sf::Color(25,25,190));
		mp_barr_max.setFillColor(sf::Color::Transparent);
		mp_barr_max.setOutlineThickness(1.0);
		mp_barr_max.setPosition(m_coord.x+30*m_scale,m_coord.y+31*m_scale);
		mp_barr_max.setScale(m_scale, m_scale);
		render->draw(mp_barr_max);

		sf::RectangleShape mp_barr;
		mp_barr.setSize(sf::Vector2f(((float)m_char->getStat()->mana()/(float)m_char->getStat()->maxMana())*100,10));
		mp_barr.setFillColor(sf::Color::Blue);
		mp_barr.setPosition(m_coord.x+30*m_scale,m_coord.y+31*m_scale);
		mp_barr.setScale(m_scale, m_scale);
		render->draw(mp_barr);
}

bool PlayerFrameInfo::event(sf::Event* event, bool used) {return used;}

} /* namespace graphics */
