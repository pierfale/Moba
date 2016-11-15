/*
 * ScreenManager.hpp
 *
 *  Created on: 14 avr. 2013
 *      Author: pierre
 */

#ifndef SCREENMANAGER_HPP_
#define SCREENMANAGER_HPP_

#include <boost/shared_ptr.hpp>
#include <string>
#include "ConnectionScreen.hpp"
#include "CharacterScreen.hpp"
#include "GameListScreen.hpp"
#include "NewCharacterScreen.hpp"
#include "SelectTeamScreen.hpp"
#include "CreateGameScreen.hpp"
#include "EndScreen.h"
#include "../../game/game/Game.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class ScreenManager {

	public:

		static CharacterScreen* character();
		static ConnectionScreen* connection();
		static GameListScreen* gameList();
		static NewCharacterScreen* newCharacter();
		static SelectTeamScreen* selectTeam(game::Game* game);
		static CreateGameScreen* createGameScreen();
		static EndScreen* endScreen();

	private:
		ScreenManager();
		static ScreenManager* getInstance();
		static boost::shared_ptr<ScreenManager> m_instance;
	};

}

#endif /* SCREENMANAGER_HPP_ */
