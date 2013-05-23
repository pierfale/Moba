/*
 * UserInterface.h
 *
 *  Created on: 24 avr. 2013
 *      Author: Béni
 */

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include <string>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "SpellBarr.h"
#include "../../../util/Coordinates.hpp"
#include "../../../game/character/Player.hpp"
#include "../../../game/game/GamePlayerList.hpp"
#include "../../component/ComponentInclude.hpp"
#include "../../layout/PassivLayout.hpp"
#include "../../layout/VerticalLayout.hpp"
#include "../../inheritedComponent/PlayerFrameInfo.h"
#include "../../InheritedListener/MenuInGameButton.h"
#include "../../layout/HorizontalLayout.hpp"
#include "../../GUIStyle.hpp"
#include "../../inheritedComponent/Chat.hpp"

namespace graphics {

class CurrentCharacter;

class UserInterface : public Container {
	public:
		UserInterface(game::Player* player);
		virtual ~UserInterface();

		void draw(sf::RenderWindow* render);
		void validate();
		void menu();
		void quit();
		void confirm();
		void removeConfirm();

	private:
		SpellBarr* m_spellBarr;
		InnerWindow* m_menu,* m_confirm;
		Button* m_button_quit,* m_button_yes,* m_button_no;
		PlayerFrameInfo* m_player_frame_info;
		PlayerFrameInfo* m_enemi_frame_info;
		boost::ptr_vector<PlayerFrameInfo> m_team_mates;
		bool m_boolMenu, m_gotTarget;
		Chat m_chat;
	};

} /* namespace graphics */
#endif /* USERINTERFACE_H_ */
