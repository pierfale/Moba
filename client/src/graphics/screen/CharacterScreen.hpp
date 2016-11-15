/*
 * CharacterScreen.hpp
 *
 *  Created on: 9 avr. 2013
 *      Author: pierre
 */

#ifndef CHARACTERSCREEN_HPP_
#define CHARACTERSCREEN_HPP_

#include "../component/ComponentInclude.hpp"
#include "../GUIStyle.hpp"
#include "../layout/LayoutInclude.hpp"
#include "../inheritedComponent/CharacterFrame.hpp"
#include "../../game/menu/PlayerList.hpp"
#include "../../game/menu/CurrentCharacter.hpp"
#include "../inheritedComponent/CharacterInfo.hpp"
#include "../inheritedComponent/CharacterSkill.hpp"
#include "../../network/Network.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class CharacterScreen : public Container {

	public:
		CharacterScreen();
		~CharacterScreen();
		void load();

		void viewChanged(void* origin);
		void characterChanged(void* origin);
		void refreshCharacter();
		std::string getComponentName();
		static std::string getName();
		Container* getMainFrame();

	private:
		Container* m_leftContainer;
		Container* m_characterContainer;
		Container* m_leftButtonContainer;
		Button* m_statButton;
		Button* m_skillButton;
		Button* m_launchButton;
		Button* m_newCharButton;
		Button* m_returnButton;
		Container* m_rightContainer;
		Container* m_upButtonContainer;
		Container* m_rightMainContainer;
		game::Player* m_playerSelected;
		boost::ptr_vector<CharacterFrame> m_chars;

	};

}


#endif /* CHARACTERSCREEN_HPP_ */
