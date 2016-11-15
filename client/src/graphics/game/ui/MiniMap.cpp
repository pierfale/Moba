/*
 * MiniMap.cpp
 *
 *  Created on: 3 juin 2013
 *      Author: pierre
 */

#include "MiniMap.hpp"

namespace graphics {

	MiniMap::MiniMap(std::string image, Gameboard* gameboard) : m_gameboard(gameboard) {
		m_texture = ImageLoader::get(image);
	}

	bool MiniMap::event(sf::Event* event, bool used) {
		return used;
	}

	void MiniMap::draw(sf::RenderWindow* render) {
		util::CoordInt coord = getRealCoord();
		sf::Sprite sprite;
		sprite.setTexture(*m_texture);
		sprite.setScale((float)m_width/(float)m_texture->getSize().x, (float)m_height/(float)m_texture->getSize().y);
		sprite.setPosition(coord.x, coord.y);
		render->draw(sprite);

		sf::RectangleShape rect(sf::Vector2f(m_width, m_height));
		rect.setPosition(coord.x, coord.y);
		rect.setOutlineThickness(1.0);
		rect.setOutlineColor(sf::Color::Black);
		rect.setFillColor(sf::Color::Transparent);
		render->draw(rect);

		float radius = 4.0;
		for(int i=0; i<game::GamePlayerList::size(); i++) {
			sf::CircleShape player(radius);
			player.setPosition(coord.x-radius+((float)game::GamePlayerList::get(i)->getCoord().x/(float)(game::GameboardModel::getWidth()*CASE_SIZE))*(float)m_width, coord.y-radius+((float)game::GamePlayerList::get(i)->getCoord().y/(float)(game::GameboardModel::getHeight()*CASE_SIZE))*(float)m_height);
			if(game::GamePlayerList::get(i)->getFaction() == game::CurrentCharacter::get()->getFaction())
				player.setFillColor(sf::Color::Green);
			else
				player.setFillColor(sf::Color::Red);
			player.setOutlineThickness(1.0);
			player.setOutlineColor(sf::Color::Black);
			render->draw(player);
		}

		sf::CircleShape player(radius);
		player.setPosition(coord.x-radius+((float)game::CurrentCharacter::get()->getCoord().x/(float)(game::GameboardModel::getWidth()*CASE_SIZE))*(float)m_width, coord.y-radius+((float)game::CurrentCharacter::get()->getCoord().y/(float)(game::GameboardModel::getHeight()*CASE_SIZE))*(float)m_height);
		player.setFillColor(sf::Color::Yellow);
		player.setOutlineThickness(1.0);
		player.setOutlineColor(sf::Color::Black);
		render->draw(player);

		sf::RectangleShape cam(sf::Vector2f(((float)m_window->getContentPane()->getWidth()/(float)(game::GameboardModel::getWidth()*CASE_SIZE))*(float)m_width, ((float)m_window->getContentPane()->getHeight()/(float)(game::GameboardModel::getHeight()*CASE_SIZE))*(float)m_height));
		cam.setPosition(coord.x+((float)m_gameboard->getCamera()->getCoord().x/(float)(game::GameboardModel::getWidth()*CASE_SIZE))*(float)m_width, coord.y+((float)m_gameboard->getCamera()->getCoord().y/(float)(game::GameboardModel::getHeight()*CASE_SIZE))*(float)m_height);
		cam.setOutlineThickness(1.0);
		cam.setOutlineColor(sf::Color::Black);
		cam.setFillColor(sf::Color::Transparent);
		render->draw(cam);

	}
}


