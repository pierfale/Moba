/*
 * Game.cpp
 *
 *  Created on: 18 avr. 2013
 *      Author: pierre
 */

#include "Game.hpp"

namespace game {

	Game::Game(int id, std::string name, std::string creator, int nPlayer) {
		m_id = id;
		m_name = name;
		m_creator = creator;
		m_nPlayer = nPlayer;
	}

	int Game::getID() {
		return m_id;
	}

	std::string Game::getName() {
		return m_name;
	}

	std::string Game::getCreator() {
		return m_creator;
	}

	int Game::getNPlayer() {
		return m_nPlayer;
	}

	void Game::setNPlayer(int n) {
		m_nPlayer = n;
	}
}


