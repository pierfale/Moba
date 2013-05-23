/*
 * UserInterface.cpp
 *
 *  Created on: 24 avr. 2013
 *      Author: Béni
 */

#include "UserInterface.h"
#include "../../../game/menu/CurrentCharacter.hpp"

namespace graphics {

	UserInterface::UserInterface(game::Player* player) : m_boolMenu(false) , m_gotTarget(false){
		setLayout(new PassivLayout());

		m_spellBarr = new SpellBarr(player);
		add(m_spellBarr);

		m_player_frame_info = new PlayerFrameInfo(player);
		m_player_frame_info->setCoord(util::CoordInt(15,15));
		m_enemi_frame_info = new PlayerFrameInfo();
		m_enemi_frame_info->setCoord(util::CoordInt(175,15));
		add(m_player_frame_info);

		m_menu = new InnerWindow("Menu",120,140, GUIStyle::innerwindow());

		m_button_quit = new Button("Quit", GUIStyle::button());
		m_button_quit->addListener(new MenuInGame_Button(this));

		m_menu->add(m_button_quit);

		m_confirm = new InnerWindow("Are you sure?",200,120,GUIStyle::innerwindow());
		m_confirm->setLayout(new HorizontalLayout());

		m_button_yes = new Button("Yes", GUIStyle::button());
		m_button_no = new Button("No", GUIStyle::button());
		m_button_yes->addListener(new MenuInGame_Button(this));
		m_button_no->addListener(new MenuInGame_Button(this));

		m_confirm->add(m_button_yes);
		m_confirm->add(m_button_no);

		for (int i = 0 ; i < game::GamePlayerList::size() ; ++i) {
			if (player->getFaction() == game::GamePlayerList::get(i)->getFaction() && player!=game::GamePlayerList::get(i) ) {
				PlayerFrameInfo* tmp = new PlayerFrameInfo(game::GamePlayerList::get(i));
				tmp->setScale(0.60);
				m_team_mates.push_back(tmp);
				add(&m_team_mates.at(i));
			}
		}
		m_chat.setCoord(util::CoordInt(500,500));
		add(&m_chat);
		validate();
	}

	UserInterface::~UserInterface() {
		delete m_spellBarr;
		delete m_menu;
		delete m_button_quit;
		delete m_confirm;
		delete m_button_no;
		delete m_button_yes;
		delete m_player_frame_info;
		delete m_enemi_frame_info;
	}

	void UserInterface::draw(sf::RenderWindow* render) {
		if (game::CurrentCharacter::getTarget() != NULL) {
			if (!m_gotTarget) {
				m_enemi_frame_info->setPlayer(game::CurrentCharacter::getTarget());
				add(m_enemi_frame_info);
				m_gotTarget = true;
			}
		} else {
			remove(m_enemi_frame_info);
			m_gotTarget = false;
		}
		Container::draw(render);
	}

	void UserInterface::validate() {
		if (m_parent==NULL) return;
		m_player_frame_info->setCoord(util::CoordInt(15,15));
		m_spellBarr->setCoord(util::CoordInt((getParent()->getWidth()/2)-((m_spellBarr->childSize()-1)*25),getParent()->getHeight()-49));
		m_menu->setCoord(util::CoordInt(getParent()->getWidth()/3,getParent()->getHeight()/3));
		m_confirm->setCoord(util::CoordInt(getParent()->getWidth()/3,getParent()->getHeight()/3));
		for (unsigned int i = 0 ; i < m_team_mates.size() ; ++i)
			m_team_mates.at(i).setCoord(util::CoordInt(0,115 + (i * 55)));
	}

	//Events
	void UserInterface::confirm() {add(m_confirm);}
	void UserInterface::removeConfirm() {remove(m_confirm);}
	void UserInterface::quit() {/*TODO QUIT();*/}
	void UserInterface::menu() {
		if (m_boolMenu) {
			remove(m_menu);
			remove(m_confirm);
			m_boolMenu = false;
		} else {
			add(m_menu);
			m_boolMenu = true;
		}
	}

} /* namespace graphics */
