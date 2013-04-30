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
#include "../../game/character/Player.hpp"
#include "../inheritedComponent/CharacterFrame.hpp"
#include "../../network/Network.hpp"

namespace graphics {

	class SelectTeamScreen : public Container {

	public:
		SelectTeamScreen(game::Game* game);
		~SelectTeamScreen();
		void load();
		std::string getComponentName();
		static std::string getName();
		void refreshPlayer();
		void buttonPressed(void* origin);

	private:
		game::Game* m_game;
		Container* m_buttonContainer;
		Container* m_buttonUpContainer;
		Container* m_buttonDownContainer;
		Container* m_mainContainer;
		Container* m_mainUpContainer;
		Container* m_team1Container;
		Container* m_team2Container;
		Container* m_mainDownContainer;
		BasicStyle* m_chatLabelStyle;
		Label* m_chatLabel;
		TextField* m_chatTextField;
		Button* m_changeTeamButton;
		Button* m_launchButton;
		Button* m_returnButton;
		boost::ptr_vector<CharacterFrame> m_chars;

	};
}


#endif /* SELECTTEAMSCREEN_HPP_ */
