/*
 * CharacterScreen.cpp
 *
 *  Created on: 9 avr. 2013
 *      Author: pierre
 */

#include "CharacterScreen.hpp"
#include "inheritedListener/CharacterScreen_MainButton.hpp"
#include "inheritedListener/CharacterScreen_CharacterButton.hpp"

namespace graphics {

	CharacterScreen::CharacterScreen() : m_playerSelected(NULL) {
		load();
	}

	void CharacterScreen::load() {
		Container* containerChar = new Container();
		this->add(containerChar);
		containerChar->setBackground("ressources/gui/background1.png", full);
		m_containerInfo = new Container();
		this->add(m_containerInfo);
		this->setLayout(new SplitFixedLayout(SplitFixedLayout::vertical, SplitFixedLayout::first, 250));
		client::Log::out("CharacterScreen Loaded");


		containerChar->setLayout(new VerticalFixedLayout(VerticalFixedLayout::fixed));

		for(int i=0; i<game::PlayerList::size(); i++) {
			CharacterFrame* cf = new CharacterFrame(game::PlayerList::get(i));
			containerChar->add(cf);
			m_chars.push_back(cf);
			cf->addListener(new CharacterScreen_CharacterButton(this));
		}

		Container* containerButton = new Container();
		m_containerInfo->add(containerButton);

		m_containerMainContent = new Container();
		m_containerMainContent->setBackgroundColor(sf::Color(30, 30, 30));
		m_containerInfo->add(m_containerMainContent);

		m_containerInfo->setLayout(new SplitFixedLayout(SplitFixedLayout::horizontal, SplitFixedLayout::first, 80));
		containerButton->setBackground("ressources/gui/background1.png", full);
		containerButton->setLayout(new HorizontalFixedLayout(HorizontalFixedLayout::full, HorizontalFixedLayout::fixed));

		CharacterScreen_MainButton* listenerMainButton = new CharacterScreen_MainButton(this);

		m_statButton = new Button("Statistic", GUIStyle::button());
		m_statButton->setSize(150, 50);
		m_statButton->addListener(listenerMainButton);
		containerButton->add(m_statButton);

		m_skillButton = new Button("Skill", GUIStyle::button());
		m_skillButton->setSize(150, 50);
		m_skillButton->addListener(listenerMainButton);
		containerButton->add(m_skillButton);

		m_launchButton = new Button("Launch", GUIStyle::button());
		m_launchButton->setSize(150, 50);
		m_launchButton->addListener(listenerMainButton);
		containerButton->add(m_launchButton);

	}

	void CharacterScreen::loadMainContent() {

	}



	void CharacterScreen::characterChanged(void* origin) {
		for(boost::ptr_vector<CharacterFrame>::iterator it = m_chars.begin(); it != m_chars.end(); ++it) {
			it->setSelect(false);
		}
		((CharacterFrame*)origin)->setSelect(true);
		m_playerSelected = ((CharacterFrame*)origin)->getPlayer();
		viewChanged(m_statButton);
	}

	void CharacterScreen::viewChanged(void* origin) {
		std::cout << util::Cast::ptrToInt(origin) << "-" << util::Cast::ptrToInt(m_statButton) << std::endl;
		if(m_playerSelected != NULL && origin == m_statButton) {
			Container* tmp = new CharacterInfo(m_playerSelected);
			m_containerInfo->replace(m_containerMainContent, tmp);
			m_containerMainContent = tmp;
			((CharacterInfo*)m_containerMainContent)->load();

		}
		else if(m_playerSelected != NULL && origin == m_skillButton) {
			Container* tmp = new CharacterSkill(m_playerSelected);
			m_containerInfo->replace(m_containerMainContent, tmp);
			m_containerMainContent = tmp;
			((CharacterSkill*)m_containerMainContent)->load();

		}
	}
}


