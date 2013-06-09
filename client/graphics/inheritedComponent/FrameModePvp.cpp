/*
 * FrameModePvp.cpp
 *
 *  Created on: 23 mai 2013
 *      Author: Béni
 */

#include "FrameModePvp.h"

namespace graphics {

FrameModePvp::FrameModePvp() {
	m_texture_background = ImageLoader::get("ressources/gui/spellBarr_background.png");
	m_font.loadFromFile("ressources/gui/font.ttf");
	m_timer.restart();
}

FrameModePvp::~FrameModePvp() {}

void FrameModePvp::draw(sf::RenderWindow* render) {
	sf::Sprite sprite;
	sprite.setTexture(*m_texture_background);
	sprite.setPosition(m_coord.x, m_coord.y);
	sprite.setOrigin(24.5,24.5);
	sprite.rotate(180.0);
	sprite.setScale(1.5,1.5);
	render->draw(sprite);

	sf::Text label;
	label.setFont(m_font);
	label.setCharacterSize(13);

	label.setColor(sf::Color::White);
	label.setPosition(m_coord.x-12 , m_coord.y);
	std::string time;
	time += util::Cast::intToString((int)m_timer.elapsed() / 60);
	time += ":";
	if ((int)m_timer.elapsed() % 60 < 10) time += util::Cast::intToString(0);
	time += util::Cast::intToString((int)m_timer.elapsed() % 60);
	label.setString(time);
	render->draw(label);


	if (game::CurrentCharacter::get()->getFaction() == network::PacketType::FACTION_TEAM1)
		label.setColor(sf::Color::Green);
	else
		label.setColor(sf::Color::Red);
	label.setPosition(m_coord.x-17 , m_coord.y+17);
	label.setString(util::Cast::intToString(game::GameboardModel::getScoreTeam(1)));
	render->draw(label);

	label.setColor(sf::Color(175,175,175));
	label.setPosition(m_coord.x-7 , m_coord.y+17);
	label.setString("VS");
	render->draw(label);

	if (game::CurrentCharacter::get()->getFaction() == network::PacketType::FACTION_TEAM2)
		label.setColor(sf::Color::Green);
	else
		label.setColor(sf::Color::Red);
	label.setPosition(m_coord.x+10 , m_coord.y+17);
	label.setString(util::Cast::intToString(game::GameboardModel::getScoreTeam(2)));
	render->draw(label);
}

bool FrameModePvp::event(sf::Event* event, bool used){return used;}
void FrameModePvp::validate(){}

} /* namespace graphics */
