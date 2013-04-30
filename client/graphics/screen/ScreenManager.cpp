/*
 * ScreenManager.cpp
 *
 *  Created on: 14 avr. 2013
 *      Author: pierre
 */

#include "ScreenManager.hpp"

namespace graphics {

	boost::shared_ptr<ScreenManager> ScreenManager::m_instance;

	ScreenManager::ScreenManager() {

	}

	CharacterScreen* ScreenManager::character() {
		return new CharacterScreen();
	}

	ConnectionScreen* ScreenManager::connection() {
		return new ConnectionScreen();
	}

	GameListScreen* ScreenManager::gameList() {
		return new GameListScreen();
	}

	NewCharacterScreen* ScreenManager::newCharacter() {
		return new NewCharacterScreen();
	}

	SelectTeamScreen* ScreenManager::selectTeam(game::Game* game) {
		return new SelectTeamScreen(game);
	}

	CreateGameScreen* ScreenManager::createGameScreen() {
		return new CreateGameScreen();
	}

	ScreenManager* ScreenManager::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new ScreenManager());
		return m_instance.get();
	}
}


