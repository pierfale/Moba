/*
 * Player.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#include "Player.hpp"

namespace game {

Player::Player(int id, std::string name, int level) : Character(id, name), m_level(level), m_nb_die(0), m_nb_frag(0)  {
	m_stat = new PlayerStat();
}

PlayerStat* Player::getStat() {
	return (PlayerStat*)m_stat;
}

int Player::getLevel() {
	return m_level;
}

void Player::incDie() {
	std::cout << m_nb_die << std::endl;
	m_nb_die++;
	std::cout << m_nb_die << std::endl;
}

void Player::incFrag() {
	m_nb_frag++;
}

int Player::getDie() {
	return m_nb_die;
}

int Player::getFrag() {
	return m_nb_frag;
}

}


