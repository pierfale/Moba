/*
 * Character.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: Béni
 */

#include "Character.h"
#include "../../game/menu/CurrentCharacter.hpp"

namespace graphics {

	Character::Character(game::Player* model) : m_model(model), m_direction(SOUTH), m_nbFrame(0), m_nextFrame(0.0), m_onMove(false), m_lastServDir(network::PacketType::DIRECTION_NONE) {
		m_texture = ImageLoader::get("ressources/game/1.png");
		m_nDirection = 0;
	}

	game::Player* Character::getModel() {
		return m_model;
	}

	void Character::event(sf::Event* event, Camera* cam, bool used, bool isPlayer) {
		if(event->type == sf::Event::MouseButtonPressed && isPlayer) {
			std::cout << (int)m_model->getCoord().x/CASE_SIZE << ';' << event->mouseButton.x/CASE_SIZE << '-' << (int)m_model->getCoord().y/CASE_SIZE << ";" << event->mouseButton.y/CASE_SIZE << std::endl;
			if((int)m_model->getCoord().x/CASE_SIZE != event->mouseButton.x/CASE_SIZE || (int)m_model->getCoord().y/CASE_SIZE != event->mouseButton.y/CASE_SIZE) {
				game::CurrentCharacter::setPath(util::PathFinding::getPath(util::CoordInt((int)m_model->getCoord().x/CASE_SIZE, (int)m_model->getCoord().y/CASE_SIZE),
					util::CoordInt(event->mouseButton.x/CASE_SIZE,event->mouseButton.y/CASE_SIZE)));
				std::cout << "crash ?" << std::endl;
				if(event->mouseButton.x/CASE_SIZE >= 0 && event->mouseButton.x/CASE_SIZE < game::GameboardModel::getWidth() &&
					event->mouseButton.y/CASE_SIZE >= 0 && event->mouseButton.y/CASE_SIZE < game::GameboardModel::getHeight() &&
					game::GameboardModel::getGameboard(0)[event->mouseButton.x/CASE_SIZE][event->mouseButton.y/CASE_SIZE]->getPassable()) {
					std::cout << "crash !!" << std::endl;
					lastDest = util::CoordInt(event->mouseButton.x, event->mouseButton.y);
				}
			}
			else {
				std::vector<util::CoordInt> v;
				game::CurrentCharacter::setPath(v);
				nextDest = util::CoordInt(event->mouseButton.x, event->mouseButton.y);
				m_onMove = true;
			}
			if(game::CurrentCharacter::getNextDest() != util::CoordInt(-1, -1)) {
				m_onMove = true;
				if(game::CurrentCharacter::isLastDest()) {
					nextDest = lastDest;
				}
				else {
					nextDest = game::CurrentCharacter::getNextDest();
					nextDest.x = nextDest.x*CASE_SIZE + CASE_SIZE/2;
					nextDest.y = nextDest.y*CASE_SIZE + CASE_SIZE/2;
				}
			}
		}
	}

	void Character::updateCoord() {
		float elapsed = m_timer.elapsed();
		m_timer.restart();
		m_nDirection = 0;
		if(m_onMove) {
			float n = m_model->getStat()->movementSpeed()*elapsed;
			float tx = nextDest.x;
			float ty = nextDest.y;
			float x = m_model->getCoord().x;
			float y = m_model->getCoord().y;

			if(tx != m_model->getCoord().x && ty != m_model->getCoord().y)
				n *= 0.7;

			if(ty != m_model->getCoord().y) {
				if(ty > m_model->getCoord().y) {
					setDirection(SOUTH);
					y = m_model->getCoord().y + n < ty ? m_model->getCoord().y + n : ty;
				}
				else {
					setDirection(NORTH);
					y = m_model->getCoord().y - n > ty ? m_model->getCoord().y - n : ty;
				}
			}
			if(tx != m_model->getCoord().x) {
				if(tx > m_model->getCoord().x) {
					setDirection(EAST);
					x = m_model->getCoord().x + n < tx ? m_model->getCoord().x + n : tx;
				}
				else {
					setDirection(WEST);
					x = m_model->getCoord().x - n > tx ? m_model->getCoord().x - n : tx;
				}
			}

			if(tx == m_model->getCoord().x && ty == m_model->getCoord().y) {
				game::CurrentCharacter::destReached();
				if(game::CurrentCharacter::getNextDest() != util::CoordInt(-1, -1)) {
					if(game::CurrentCharacter::isLastDest()) {
						nextDest = lastDest;
					}
					else {
						nextDest = game::CurrentCharacter::getNextDest();
						nextDest.x = nextDest.x*CASE_SIZE + CASE_SIZE/2;
						nextDest.y = nextDest.y*CASE_SIZE + CASE_SIZE/2;
					}
				}
				else {
					m_onMove = false;
					m_nbFrame = 0;

				}
			}
			util::CoordFloat extra = m_model->getCoordExtra();
			m_model->setCoord(util::CoordFloat(x+extra.x,y+extra.y));


			m_nextFrame += elapsed;
			if(m_nextFrame > CHARACTER_TIME_BETWEEN_FRAME) {
				m_nbFrame = (m_nbFrame+1)%4;
				m_nextFrame = m_nextFrame-FRAME_TIME;
			}

		}

		checkMovement();
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

	void Character::checkMovement() {
		if(m_nDirection == 0)
			m_model->setDirection(network::PacketType::DIRECTION_NONE);

		if(m_model->getDirection() != m_lastServDir) {
			network::Packet packet(network::Network::getSocket(), network::PacketType::GAME_ASKMOVE);
			packet << m_model->getCoord().x << m_model->getCoord().y << m_model->getDirection();
			packet.send();
		}
		m_lastServDir = m_model->getDirection();

	}

	void Character::calculCoord() {
		float elapsed = m_timer.elapsed();
		m_timer.restart();
		float x = m_model->getCoord().x;
		float y = m_model->getCoord().y;
		if(m_model->getDirection() == network::PacketType::DIRECTION_NORTH) {
			m_direction = NORTH;
			m_model->setCoord(util::CoordFloat(x, y-m_model->getStat()->movementSpeed()*elapsed));
		}
		if(m_model->getDirection() == network::PacketType::DIRECTION_SOUTH) {
			m_direction = SOUTH;
			m_model->setCoord(util::CoordFloat(x, y+m_model->getStat()->movementSpeed()*elapsed));
		}
		if(m_model->getDirection() == network::PacketType::DIRECTION_EAST) {
			m_direction = EAST;
			m_model->setCoord(util::CoordFloat(x+m_model->getStat()->movementSpeed()*elapsed, y));
		}
		if(m_model->getDirection() == network::PacketType::DIRECTION_WEST) {
			m_direction = WEST;
			m_model->setCoord(util::CoordFloat(x-m_model->getStat()->movementSpeed()*elapsed, y));
		}
		if(m_model->getDirection() == network::PacketType::DIRECTION_NORTHEAST) {
			m_direction = EAST;
			m_model->setCoord(util::CoordFloat(x+CHARACTER_DIAG_RATIO*m_model->getStat()->movementSpeed()*elapsed, y-CHARACTER_DIAG_RATIO*m_model->getStat()->movementSpeed()*elapsed));
		}
		if(m_model->getDirection() == network::PacketType::DIRECTION_NORTHWEST) {
			m_direction = WEST;
			m_model->setCoord(util::CoordFloat(x-CHARACTER_DIAG_RATIO*m_model->getStat()->movementSpeed()*elapsed, y-CHARACTER_DIAG_RATIO*m_model->getStat()->movementSpeed()*elapsed));
		}
		if(m_model->getDirection() == network::PacketType::DIRECTION_SOUTHEAST) {
			m_direction = EAST;
			m_model->setCoord(util::CoordFloat(x+CHARACTER_DIAG_RATIO*m_model->getStat()->movementSpeed()*elapsed, y+CHARACTER_DIAG_RATIO*m_model->getStat()->movementSpeed()*elapsed));
		}
		if(m_model->getDirection() == network::PacketType::DIRECTION_SOUTHWEST) {
			m_direction = WEST;
			m_model->setCoord(util::CoordFloat(x-CHARACTER_DIAG_RATIO*m_model->getStat()->movementSpeed()*elapsed, y+CHARACTER_DIAG_RATIO*m_model->getStat()->movementSpeed()*elapsed));
		}
		if(m_model->getDirection() == network::PacketType::DIRECTION_NONE) {
			m_nbFrame = 0;
			m_onMove = false;
		}
		util::CoordFloat extra = m_model->getCoordExtra();
		m_model->setCoord(util::CoordFloat(m_model->getCoord().x+extra.x,m_model->getCoord().y+extra.y));
		m_nextFrame += elapsed;
		if(m_nextFrame > CHARACTER_TIME_BETWEEN_FRAME) {
			m_nbFrame = (m_nbFrame+1)%4;
			m_nextFrame = m_nextFrame-FRAME_TIME;
		}
	}

	void Character::draw(sf::RenderWindow* render, Camera* cam) {
		m_sprite.setTexture(*m_texture);
		m_sprite.setTextureRect(sf::IntRect(50*m_nbFrame,85*m_direction,50,85));
		m_sprite.setPosition(m_model->getCoord().x-CHARACTER_OFFSET_X, m_model->getCoord().y-CHARACTER_OFFSET_Y);
		render->draw(m_sprite);

		sf::RectangleShape rect(sf::Vector2f(4, 4));
		rect.setPosition(m_model->getCoord().x-2, m_model->getCoord().y-2);
		render->draw(rect);

		sf::RectangleShape rect2(sf::Vector2f(4, 4));
		rect2.setPosition(nextDest.x-2, nextDest.y-2);
		render->draw(rect2);
	}
}
