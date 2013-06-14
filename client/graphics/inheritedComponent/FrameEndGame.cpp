/*
 * FrameEndGame.cpp
 *
 *  Created on: 23 mai 2013
 *      Author: Béni
 */

#include "FrameEndGame.h"

namespace graphics {

FrameEndGame::FrameEndGame() {
	m_texture_background = ImageLoader::get("ressources/gui/playerInfo_background.png");
	m_texture_icon = ImageLoader::get("ressources/game/icon.png");
	m_font.loadFromFile("ressources/gui/font.ttf");
}

FrameEndGame::~FrameEndGame() {
	delete m_texture_background;
	delete m_texture_icon;
}

void FrameEndGame::draw(sf::RenderWindow* render) {
	int cpt = 2;
	drawHeader(render);
	drawPlayerInfo(render, game::CurrentCharacter::get(), 1);
	for (int i = 0 ; i < game::GamePlayerList::size() ; i++) {
			if (game::GamePlayerList::get(i)->getFaction() ==  game::CurrentCharacter::get()->getFaction()) {
			drawPlayerInfo(render, game::GamePlayerList::get(i), cpt);
			cpt++;
		}
	}
	for (int i = 0 ; i < game::GamePlayerList::size() ; i++) {
		if (game::GamePlayerList::get(i)->getFaction() !=  game::CurrentCharacter::get()->getFaction()) {
			drawPlayerInfo(render, game::GamePlayerList::get(i), cpt);
			cpt++;
		}
	}
}

bool FrameEndGame::event(sf::Event* event, bool used){return used;}

void FrameEndGame::drawHeader(sf::RenderWindow* render) {

	sf::Sprite sprite;
	sprite.setTexture(*m_texture_background);
	sprite.setScale(3.21, 1.0);
	sprite.setPosition(5,5);
	render->draw(sprite);

	sprite.setScale(1.0, 1.0);

	sf::Text label;
	label.setFont(m_font);
	label.setCharacterSize(13);
	label.setColor(sf::Color::White);

	label.setString("Team");
	label.setPosition(15,20);
	render->draw(label);

	label.setString("Name");
	label.setPosition(65,20);
	render->draw(label);

	label.setString("LvL");
	label.setPosition(145,20);
	render->draw(label);

	sprite.setTexture(*m_texture_icon);

	sprite.setTextureRect(sf::IntRect(0,0,25,25));
	sprite.setPosition(195,15);
	render->draw(sprite);

	sprite.setTextureRect(sf::IntRect(0,25,25,25));
	sprite.setPosition(245,15);
	render->draw(sprite);

	sprite.setTextureRect(sf::IntRect(175,0,25,25));
	sprite.setPosition(295,15);
	render->draw(sprite);

	if (game::GameboardModel::getIdMode() != 2)
		sprite.setColor(sf::Color(10,10,10));

	sprite.setTextureRect(sf::IntRect(25,25,25,25));
	sprite.setPosition(345,15);
	render->draw(sprite);

	sprite.setTextureRect(sf::IntRect(50,25,25,25));
	sprite.setPosition(395,15);
	render->draw(sprite);

}
void FrameEndGame::drawPlayerInfo(sf::RenderWindow* render, game::Player* player, int index) {
	sf::Sprite sprite;
	int team;
	if (player->getFaction() == 15) //TODO use the PacketType
		team = 1 ;
	else
		team = 2;

	if (player->getFaction() == game::CurrentCharacter::get()->getFaction())
		sprite.setColor(sf::Color(0,255,0));
	else
		sprite.setColor(sf::Color(255,0,0));

	sprite.setTexture(*m_texture_background);
	sprite.setScale(3.21, 1.0);
	sprite.setPosition(5,5+index*49);
	render->draw(sprite);

	sprite.setColor(sf::Color(255,255,255));
	sprite.setScale(1.0, 1.0);

	sf::Text label;
	label.setFont(m_font);
	label.setCharacterSize(13);
	label.setColor(sf::Color::White);


	label.setString(util::Cast::intToString(team));
	label.setPosition(15,20+index*49);
	render->draw(label);

	label.setString(player->getName());
	label.setPosition(65,20+index*49);
	render->draw(label);

	label.setString(util::Cast::intToString(player->getLevel()));
	label.setPosition(145,20+index*49);
	render->draw(label);

	//Frags
	label.setString(util::Cast::intToString(player->getFrag()));
	label.setPosition(205,15+index*49);
	render->draw(label);

	//Die
	label.setString(util::Cast::intToString(player->getDie()));
	label.setPosition(255,15+index*49);
	render->draw(label);

	//Gold
	label.setString(util::Cast::intToString(0));
	label.setPosition(305,15+index*49);
	render->draw(label);

	if (game::GameboardModel::getIdMode() != 2)
		sprite.setColor(sf::Color(10,10,10));

	sprite.setTextureRect(sf::IntRect(25,25,25,25));
	sprite.setPosition(345,15+index*49);
	render->draw(sprite);

	sprite.setTextureRect(sf::IntRect(50,25,25,25));
	sprite.setPosition(395,15+index*49);
	render->draw(sprite);
}

} /* namespace graphics */
