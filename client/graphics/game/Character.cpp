/*
 * Character.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: Béni
 */

#include "Character.h"

namespace graphics {

	Character::Character(std::string name) : m_name(name) , m_nbFrame(0), m_xTarget(0), m_yTarget(0), m_onMove(false), m_direction(SOUTH), m_coord(5,5) {
		m_texture = NULL; m_sprite = NULL;
	}
	Character::~Character() { free(m_sprite); }
	std::string Character::toString() { return ""; }

	//graphics manage
	void Character::load(Window* window) {
		window->getImageLoader()->add("ressources/game/1.png");
		m_texture = window->getImageLoader()->get("ressources/game/1.png");
		m_sprite = new sf::Sprite();
	}
	void Character::incFrame() {if (m_nbFrame == 3) m_nbFrame = 0; else m_nbFrame++;}


	//getters
	int Character::getDirection() {return m_direction;}
	sf::Sprite* Character::getSprite(){return m_sprite;}
	sf::Texture* Character::getTexture(){return m_texture;}
	util::Coordinates Character::getCoordinates(){return m_coord;}
	bool Character::getOnMove() {return m_onMove;}
	int Character::getFrame() {return m_nbFrame; }

	//setters
	void Character::setCoord(int x, int y) {m_coord.x = x; m_coord.y = y;}
	void Character::setDirection(int dir) { m_direction = Direction(dir); }

	//pathfinding
	std::vector<util::Coordinates> Character::getPathAs() { return NULL;}

} /* namespace graphics */
