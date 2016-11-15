/*
 * GameListScreen.hpp
 *
 *  Created on: 16 avr. 2013
 *      Author: pierre
 */

#ifndef GAMELISTSCREEN_HPP_
#define GAMELISTSCREEN_HPP_

#include "../component/ComponentInclude.hpp"
#include "../GUIStyle.hpp"
#include "../layout/LayoutInclude.hpp"
#include "../../game/menu/GameList.hpp"
#include "../../game/game/Game.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class GameListScreen : public Container {

	public:
		GameListScreen();
		~GameListScreen();
		void load();
		void buttonPressed(void* origin);
		void gameChanged(void* origin);
		void refreshGame();
		std::string getComponentName();
		static std::string getName();

	private:
		Container* m_buttonContainer;
		Container* m_buttonUpContainer;
		Container* m_buttonDownContainer;
		Container* m_mainContainer;
		Button* m_matchmakingButton;
		Button* m_joinButton;
		Button* m_createButton;
		Button* m_returnButton;
		game::Game* m_gameSelected;
		Table* m_table;
		BasicStyle* m_tableStyle;

	};
}


#endif /* GAMELISTSCREEN_HPP_ */
