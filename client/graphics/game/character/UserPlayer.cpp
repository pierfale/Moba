/*
 * UserPlayer.cpp
 *
 *  Created on: 7 mai 2013
 *      Author: pierre
 */

#include "UserPlayer.hpp"
#include "../../../game/menu/CurrentCharacter.hpp"

namespace graphics {

	UserPlayer::UserPlayer(game::Player* model) : Player(model) {

	}

	bool UserPlayer::event(sf::Event* event, Camera* cam, bool used) {
		if(!used && event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Right) {
			util::CoordInt goal = util::CoordInt(event->mouseButton.x, event->mouseButton.y);
			this->moveTo(goal);
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
	}

	void UserPlayer::update() {
		checkTarget();
		updateCoord();
	}

	void UserPlayer::checkTarget() {
		/*
		if(m_state == CHARACTER_STATE_GOTO_TARGET) {
			if(util::Math::distance(game::CurrentCharacter::getTarget()->getCoord(), m_model->getCoord()) < m_model->getStat()->range()-5) {
				network::Packet packet(network::Network::getSocket(), network::PacketType::GAME_ASKLAUNCHSINGLETARGETSPELL);
				packet << 1 << game::CurrentCharacter::getTarget()->getID();
				packet.send();
				setState(CHARACTER_STATE_GOTO_TARGET_ATTACK);
			}
			else {
				//if target move
				int n = 10;
				if(util::Math::distance(game::CurrentCharacter::getTarget()->getCoord(), util::CoordFloat(m_lastDest.x, m_lastDest.y)) > n) {
					this->moveTo(util::CoordInt(game::CurrentCharacter::getTarget()->getCoord().x, game::CurrentCharacter::getTarget()->getCoord().y));
				}
			}
		}
		else if(m_state == CHARACTER_STATE_GOTO_TARGET_ATTACK) {
			if(util::Math::distance(game::CurrentCharacter::getTarget()->getCoord(), m_model->getCoord()) > m_model->getStat()->range()) {
				setState(CHARACTER_STATE_GOTO_TARGET);
			}
		}
		*/
	}

	void UserPlayer::updateCoord() {
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
			else if(m_model->getDirection() == network::PacketType::DIRECTION_NONE) {
				setState(CHARACTER_STATE_NOMOVE);
				m_nbFrame = 0;
			}

			util::CoordFloat extra = m_model->getCoordExtra();
			m_model->setCoord(util::CoordFloat(m_model->getCoord().x-extra.x,m_model->getCoord().y-extra.y));
			if(m_model->getDirection() != network::PacketType::DIRECTION_NONE) {
				m_nextFrame += elapsed;
				if(m_nextFrame > CHARACTER_TIME_BETWEEN_FRAME) {
					m_nbFrame = (m_nbFrame+1)%4;
					m_nextFrame = m_nextFrame-FRAME_TIME;
				}
			}

	}

	void UserPlayer::checkMovement() {


	}

	void UserPlayer::moveTo(util::CoordInt goal) {
		util::CoordInt start = util::CoordInt(m_model->getCoord().x, m_model->getCoord().y);
		if(start.x/CASE_SIZE != goal.x/CASE_SIZE || start.y/CASE_SIZE != goal.y/CASE_SIZE) {
			std::vector<util::CoordInt> path = util::PathFinding::getPath(util::CoordInt(start.x/CASE_SIZE, start.y/CASE_SIZE),
						util::CoordInt(goal.x/CASE_SIZE, goal.y/CASE_SIZE));
			std::vector<util::CoordInt> pathFinal;
			if(path.size() > 0) {
				for(unsigned int i = 0 ; i< path.size(); i++) {
					pathFinal.push_back(util::CoordInt(path.at(i).x*CASE_SIZE+CASE_SIZE/2, path.at(i).y*CASE_SIZE+CASE_SIZE/2));
				}
				if(pathFinal.at(pathFinal.size()-1) != goal) {
					pathFinal.pop_back();
					pathFinal.push_back(goal);
				}
				network::Packet packet(network::Network::getSocket(), network::PacketType::GAME_ASKMOVE);
				packet << (int)pathFinal.size();
				for(unsigned int i=0; i<pathFinal.size(); i++)
					packet << pathFinal.at(i).x << pathFinal.at(i).y;
				packet.send();
			}
		}
	}

	void UserPlayer::setState(int state) {
		if(state == CHARACTER_STATE_GOTO && m_state == CHARACTER_STATE_GOTO_TARGET) {
			//nop
		}
		else {
			m_state = state;
		}
	}

	void UserPlayer::draw(sf::RenderWindow* render, Camera* cam) {
		m_sprite.setTexture(*m_texture);
		m_sprite.setTextureRect(sf::IntRect(m_textureWidth*m_nbFrame, m_textureHeight*m_direction, m_textureWidth, m_textureHeight));
		m_sprite.setPosition(m_model->getCoord().x-m_textureWidth/2-cam->getCoord().x, m_model->getCoord().y-m_textureHeight-cam->getCoord().y);
		if(m_focus) {
			m_sprite.setColor(sf::Color::Green);
			sf::CircleShape range(m_model->getStat()->range());
			range.setFillColor(sf::Color::Transparent);
			range.setOutlineColor(sf::Color::Green);
			range.setOutlineThickness(3);
			range.setPosition(m_model->getCoord().x-cam->getCoord().x-m_model->getStat()->range(), m_model->getCoord().y-cam->getCoord().y-m_model->getStat()->range());
			render->draw(range);
		}
		else
			m_sprite.setColor(sf::Color::White);
		render->draw(m_sprite);

		sf::Text pseudo(m_model->getName());
		pseudo.setCharacterSize(12);
		pseudo.setPosition(m_model->getCoord().x-pseudo.getGlobalBounds().width/2-cam->getCoord().x, m_model->getCoord().y-m_textureHeight-pseudo.getGlobalBounds().width/2-cam->getCoord().y);
		render->draw(pseudo);
	}
}
