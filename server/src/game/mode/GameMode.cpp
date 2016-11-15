/*
 * GameMode.cpp
 *
 *  Created on: 28 avr. 2013
 *      Author: pierre
 */

#include "GameMode.hpp"
#include "../Game.hpp"

GameMode::~GameMode() {

}

void GameMode::setGame(Game* game) {
	m_game = game;
}

std::string GameMode::getMap() {
	return m_map;
}


