/*
 * SelectTeamScreen.hpp
 *
 *  Created on: 19 avr. 2013
 *      Author: pierre
 */

#ifndef SELECTTEAMSCREEN_HPP_
#define SELECTTEAMSCREEN_HPP_

#include "../component/ComponentInclude.hpp"
#include "../GUIStyle.hpp"
#include "../layout/LayoutInclude.hpp"
#include "../../game/game/Game.hpp"

namespace graphics {

	class SelectTeamScreen : public Container {

	public:
		SelectTeamScreen(game::Game* game);
		~SelectTeamScreen();
		void load();

	private:
		game::Game* m_game;
		Container* m_buttonContainer;
		Container* m_buttonUpContainer;
		Container* m_buttonDownContainer;
		Container* m_mainContainer;
		Container* m_mainUpContainer;
		Container* m_mainDownContainer;
		BasicStyle* m_chatLabelStyle;
		Label* m_chatLabel;
		TextField* m_chatTextField;
		Button* m_changeTeamButton;
		Button* m_returnButton;

	};
}


#endif /* SELECTTEAMSCREEN_HPP_ */
