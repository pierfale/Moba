/*
 * Player.cpp
 *
 *  Created on: 10 avr. 2013
 *      Author: Béni
 */

#include "Player.h"

namespace graphics {

	Player::Player(std::string name) : Character(name) {}
	Player::~Player() {}

	void Player::event(sf::Event* event) {
		if (event->type == sf::Event::MouseButtonPressed) {
			if (event->mouseButton.button == sf::Mouse::Right) {
				setTarget(event->mouseButton.x,event->mouseButton.x);
				m_onMove = true;
			}
		}
	}

	void Player::moveTo(int x, int y) {

	}

	void Player::setTarget(int x, int y){m_xTarget = x; m_yTarget = y;}

} /* namespace graphics */
