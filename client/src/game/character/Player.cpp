/*
 * Player.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#include "Player.hpp"

namespace game {

Player::Player(int id, std::string name, int level, int exp) : Character(id, name), m_level(level), m_nb_die(0), m_nb_frag(0), m_exp(exp), m_expEarned(0) {
	m_stat = new PlayerStat();
	m_expRequired = (m_level * 5) +10;
}

PlayerStat* Player::getStat() {
	return (PlayerStat*)m_stat;
}

int Player::getLevel() {
	return m_level;
}

void Player::incDie() {
	m_nb_die++;
}

void Player::incFrag() {
	m_nb_frag++;
}

void Player::incExp() {
	m_exp++;
}

void Player::setExpEarned(int expEarned) {
	m_expEarned = expEarned;
}

int Player::getDie() {
	return m_nb_die;
}

int Player::getFrag() {
	return m_nb_frag;
}

int Player::getExp() {
	return m_exp;
}

int Player::getExpEarned() {
	return m_expEarned;
}

int Player::getExpRequired() {
	return m_expRequired;
}

}


