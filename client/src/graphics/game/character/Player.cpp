/*
 * Player.cpp
 *
 *  Created on: 7 mai 2013
 *      Author: pierre
 */

#include "Player.hpp"
#include "../../../game/menu/CurrentCharacter.hpp"

namespace graphics {

	Player::Player(game::Player* model) : Character(model) {
		m_textureWidth = 50;
		m_textureHeight = 85;
	}

	Player::~Player() {

	}

	bool Player::event(sf::Event* event, Camera* cam, bool used) {
		if(!used && event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left) {

			if(event->mouseButton.x >= m_model->getCoord().x-m_textureWidth/2-cam->getCoord().x && event->mouseButton.x < m_model->getCoord().x+m_textureWidth/2-cam->getCoord().x &&
					event->mouseButton.y >= m_model->getCoord().y-m_textureHeight-cam->getCoord().y && event->mouseButton.y < m_model->getCoord().y-cam->getCoord().y &&
					ImageLoader::getImage("ressources/game/1.png")->getPixel(m_textureWidth*m_nbFrame+event->mouseButton.x-(m_model->getCoord().x-m_textureWidth/2-cam->getCoord().x), m_textureHeight*m_direction+event->mouseButton.y-(m_model->getCoord().y-m_textureHeight-cam->getCoord().y)).a > 200) {
				used = true;
				if(game::CurrentSpell::get() != NULL) {
					network::Packet packet(network::Network::getSocket(), network::PacketType::GAME_ASKLAUNCHSINGLETARGETSPELL);
					packet << game::CurrentSpell::get()->getId() << m_model->getID();
					packet.send();
					game::CurrentSpell::set(NULL);
				}
				else {
					network::Packet packet(network::Network::getSocket(), network::PacketType::GAME_ASKTARGET);
					packet << m_model->getID();
					packet.send();
				}
			}

		}
		else if(event->type == sf::Event::MouseMoved) {
			if(!used && event->mouseMove.x >= m_model->getCoord().x-m_textureWidth/2-cam->getCoord().x && event->mouseMove.x < m_model->getCoord().x+m_textureWidth/2-cam->getCoord().x &&
					event->mouseMove.y >= m_model->getCoord().y-m_textureHeight-cam->getCoord().y && event->mouseMove.y < m_model->getCoord().y-cam->getCoord().y &&
					ImageLoader::getImage("ressources/game/1.png")->getPixel(m_textureWidth*m_nbFrame+event->mouseMove.x-(m_model->getCoord().x-m_textureWidth/2-cam->getCoord().x), m_textureHeight*m_direction+event->mouseMove.y-(m_model->getCoord().y-m_textureHeight-cam->getCoord().y)).a > 200) {
					m_focus = true;
					used = true;
			}
			else
				m_focus = false;
		}
		return used;
		return used;
	}

	void Player::update() {
		updateCoord();
	}

	void Player::updateCoord() {
		float elapsed = m_timer.elapsed();
		m_timer.restart();
		float x = m_model->getCoord().x;
		float y = m_model->getCoord().y;
		if(m_model->getDirection() == network::PacketType::DIRECTION_NORTH) {
			m_direction = NORTH;
			m_model->setCoord(util::CoordFloat(x, y-m_model->getStat()->movementSpeed()*elapsed));
		}
		else if(m_model->getDirection() == network::PacketType::DIRECTION_SOUTH) {
			m_direction = SOUTH;
			m_model->setCoord(util::CoordFloat(x, y+m_model->getStat()->movementSpeed()*elapsed));
		}
		else if(m_model->getDirection() == network::PacketType::DIRECTION_EAST) {
			m_direction = EAST;
			m_model->setCoord(util::CoordFloat(x+m_model->getStat()->movementSpeed()*elapsed, y));
		}
		else if(m_model->getDirection() == network::PacketType::DIRECTION_WEST) {
			m_direction = WEST;
			m_model->setCoord(util::CoordFloat(x-m_model->getStat()->movementSpeed()*elapsed, y));
		}
		else if(m_model->getDirection() == network::PacketType::DIRECTION_NORTHEAST) {
			m_direction = EAST;
			m_model->setCoord(util::CoordFloat(x+CHARACTER_DIAG_RATIO*m_model->getStat()->movementSpeed()*elapsed, y-CHARACTER_DIAG_RATIO*m_model->getStat()->movementSpeed()*elapsed));
		}
		else if(m_model->getDirection() == network::PacketType::DIRECTION_NORTHWEST) {
			m_direction = WEST;
			m_model->setCoord(util::CoordFloat(x-CHARACTER_DIAG_RATIO*m_model->getStat()->movementSpeed()*elapsed, y-CHARACTER_DIAG_RATIO*m_model->getStat()->movementSpeed()*elapsed));
		}
		else if(m_model->getDirection() == network::PacketType::DIRECTION_SOUTHEAST) {
			m_direction = EAST;
			m_model->setCoord(util::CoordFloat(x+CHARACTER_DIAG_RATIO*m_model->getStat()->movementSpeed()*elapsed, y+CHARACTER_DIAG_RATIO*m_model->getStat()->movementSpeed()*elapsed));
		}
		else if(m_model->getDirection() == network::PacketType::DIRECTION_SOUTHWEST) {
			m_direction = WEST;
			m_model->setCoord(util::CoordFloat(x-CHARACTER_DIAG_RATIO*m_model->getStat()->movementSpeed()*elapsed, y+CHARACTER_DIAG_RATIO*m_model->getStat()->movementSpeed()*elapsed));
		}


		if(m_model->getDirection() != network::PacketType::DIRECTION_NONE) {
			util::CoordFloat extra = m_model->getCoordExtra();
			m_model->setCoord(util::CoordFloat(m_model->getCoord().x-extra.x,m_model->getCoord().y-extra.y));
			m_nextFrame += elapsed;
			if(m_nextFrame > CHARACTER_TIME_BETWEEN_FRAME) {
				m_nbFrame = (m_nbFrame+1)%4;
				m_nextFrame = m_nextFrame-FRAME_TIME;
			}
		}
		else
			m_nbFrame = 0;
	}
}


