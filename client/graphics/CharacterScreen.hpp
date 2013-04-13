/*
 * CharacterScreen.hpp
 *
 *  Created on: 9 avr. 2013
 *      Author: pierre
 */

#ifndef CHARACTERSCREEN_HPP_
#define CHARACTERSCREEN_HPP_

#include "component/Container.hpp"
#include "component/ComponentInclude.hpp"
#include "GUIStyle.hpp"
#include "layout/LayoutInclude.hpp"
#include "inheritedComponent/CharacterFrame.hpp"
#include "../game/menu/PlayerList.hpp"
#include "inheritedComponent/CharacterInfo.hpp"
#include "inheritedComponent/CharacterSkill.hpp"


namespace graphics {

	class CharacterScreen : public Container {

	public:
		CharacterScreen();
		void load();

		void viewChanged(void* origin);
		void characterChanged(void* origin);
		void loadMainContent();

	private:
		Button* m_statButton;
		Button* m_skillButton;
		Button* m_launchButton;
		Container* m_containerMainContent;
		Container* m_containerInfo;
		game::Player* m_playerSelected;
		boost::ptr_vector<CharacterFrame> m_chars;

	};

}


#endif /* CHARACTERSCREEN_HPP_ */
