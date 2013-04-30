/*
 * Character.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: Béni
 */

#include "Character.h"

namespace graphics {

	Character::Character( game::Player* player) : m_nbFrame(0),  m_onMove(false), m_direction(SOUTH), m_target(0,0) {
		m_player = player;
		m_texture = ImageLoader::get("ressources/game/1.png");
		m_sprite = new sf::Sprite();
	}
	Character::~Character() {free(m_sprite);}

	void Character::incFrame() {if (m_nbFrame == 3) m_nbFrame = 0; else m_nbFrame++;}

	void Character::event(sf::Event* event, Camera cam, bool client) {
		if (event->type == sf::Event::MouseButtonPressed) {
			if (event->mouseButton.button == sf::Mouse::Right) {
				if (client) {
					setTarget(+cam.getCoord().x+event->mouseButton.x,+cam.getCoord().y+event->mouseButton.y);
					m_onMove = true;
				} else {
					if (event->mouseButton.x >= m_player->getCoord().x &&
							event->mouseButton.x < m_player->getCoord().x+50 &&
							event->mouseButton.y >= m_player->getCoord().y &&
							event->mouseButton.y < m_player->getCoord().y+85) {
						if (ImageLoader::getImage("ressources/game/1.png")->getPixel(cam.getCoord().x+event->mouseButton.x, cam.getCoord().y+event->mouseButton.y) != sf::Color::Transparent)
							std::cout << "TARGET!!"<< std::endl;
					}
				}
			}
		}
	}

	void Character::draw(sf::RenderWindow* render, Camera cam) {
		if (m_onMove) {
			if (m_frame.elapsed() > (m_player->getStat()->movementSpeed()/50)) {moveTo() ; m_frame.restart();incFrame();}
		} else m_nbFrame = 0 ;
		m_sprite->setTexture(*m_texture);
		sf::Rect<int> spriteZone(50*m_nbFrame,85*m_direction,50,85);
		m_sprite->setTextureRect(spriteZone);
		m_sprite->setPosition((-cam.getCoord().x+m_player->getCoord().x),
				(-cam.getCoord().y+m_player->getCoord().y));
		render->draw(*m_sprite);
	}

	void Character::moveTo() {
		if (abs(m_player->getCoord().y - m_target.y) < m_player->getStat()->movementSpeed())
			m_player->setCoord(m_player->getCoord().x, m_target.y);
		else {
			if (m_player->getCoord().y > m_target.y){
				m_direction = Direction(NORTH);
				m_player->setCoord(m_player->getCoord().x,m_player->getCoord().y-m_player->getStat()->movementSpeed());
			} else {
				m_direction = Direction(SOUTH);
				m_player->setCoord(m_player->getCoord().x,m_player->getCoord().y+m_player->getStat()->movementSpeed());
			}
		}
		if (abs(m_player->getCoord().x - m_target.x) < m_player->getStat()->movementSpeed())
				m_player->setCoord(m_target.x, m_player->getCoord().y);
		else {
			if (m_player->getCoord().x > m_target.x) {
				m_direction = Direction(WEST);
				m_player->setCoord(m_player->getCoord().x-m_player->getStat()->movementSpeed(),m_player->getCoord().y);
			} else {
				m_direction = Direction(EAST);
				m_player->setCoord(m_player->getCoord().x+m_player->getStat()->movementSpeed(),m_player->getCoord().y);
			}
		}
		if (m_player->getCoord() == m_target) m_onMove = false;
	}

	void Character::setTarget(int x, int y){
		m_target.x = x - 25;
		m_target.x -= m_target.x % ((int) m_player->getStat()->movementSpeed());
		m_target.y = y - 85;
		m_target.y -= m_target.y % ((int) m_player->getStat()->movementSpeed());
	}

	//getters
	int Character::getDirection() {return m_direction;}
	sf::Texture* Character::getTexture(){return m_texture;}
	bool Character::getOnMove() {return m_onMove;}
	int Character::getFrame() {return m_nbFrame; }
	game::Player* Character::getPlayerModel() {return m_player;}

	//setters
	void Character::setDirection(int dir) { m_direction = Direction(dir); }

} /* namespace graphics */
