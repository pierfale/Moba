/*
 * Character.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: Béni
 */

#include "Character.hpp"
#include "../../../game/menu/CurrentCharacter.hpp"

namespace graphics {

	Character::Character(game::Character* model) : m_model(model), m_direction(SOUTH), m_nbFrame(0), m_nextFrame(0.0) {
		m_texture = ImageLoader::get("ressources/game/1.png");
		m_textureWidth = 0;
		m_textureHeight = 0;
		m_nDirection = 0;
		m_focus = false;
		m_state = CHARACTER_STATE_NOMOVE;
	}

	Character::~Character() {

	}

	game::Character* Character::getModel() {
		return m_model;
	}

	bool Character::event(sf::Event* event, Camera* cam, bool used) {
		return used;
	}

	void Character::setDirection(Direction dir) {
		if(m_nDirection == 0) {
			if(dir == NORTH)
				m_model->setDirection(network::PacketType::DIRECTION_NORTH);
			if(dir == SOUTH)
				m_model->setDirection(network::PacketType::DIRECTION_SOUTH);
			if(dir == WEST)
				m_model->setDirection(network::PacketType::DIRECTION_WEST);
			if(dir == EAST)
				m_model->setDirection(network::PacketType::DIRECTION_EAST);
		}
		else if(m_nDirection == 1) {
			if(m_direction == NORTH && dir == WEST)
				m_model->setDirection(network::PacketType::DIRECTION_NORTHWEST);
			if(m_direction == NORTH && dir == EAST)
				m_model->setDirection(network::PacketType::DIRECTION_NORTHEAST);
			if(m_direction == SOUTH && dir == WEST)
				m_model->setDirection(network::PacketType::DIRECTION_SOUTHWEST);
			if(m_direction == SOUTH && dir == EAST)
				m_model->setDirection(network::PacketType::DIRECTION_SOUTHEAST);
		}
		m_direction = dir;
		m_nDirection++;
	}

	void Character::setState(int state) {
		m_state = state;
	}

	int Character::getValueY() {
		return m_model->getCoord().y;
	}

	void Character::draw(sf::RenderWindow* render, Camera* cam) {
		m_sprite.setTexture(*m_texture);
		m_sprite.setTextureRect(sf::IntRect(m_textureWidth*m_nbFrame, m_textureHeight*m_direction, m_textureWidth, m_textureHeight));
		m_sprite.setPosition(m_model->getCoord().x-m_textureWidth/2-cam->getCoord().x, m_model->getCoord().y-m_textureHeight-cam->getCoord().y);
		if(m_focus) {
			if(game::CurrentCharacter::get()->getFaction() == m_model->getFaction() || m_model->getFaction() == network::PacketType::FACTION_PEACEFUL)
				m_sprite.setColor(sf::Color::Green);
			else
				m_sprite.setColor(sf::Color::Red);
		}
		else
			m_sprite.setColor(sf::Color::White);
		render->draw(m_sprite);

		sf::Text pseudo(m_model->getName());
		pseudo.setCharacterSize(12);
		pseudo.setPosition(m_model->getCoord().x-pseudo.getGlobalBounds().width/2-cam->getCoord().x, m_model->getCoord().y-m_textureHeight-pseudo.getGlobalBounds().width/2-cam->getCoord().y);
		render->draw(pseudo);

	}

	void Character::launchSpell() {

	}
}
