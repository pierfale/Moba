/*
 * CharacterScreen.cpp
 *
 *  Created on: 9 avr. 2013
 *      Author: pierre
 */

#include "CharacterScreen.hpp"
#include "../inheritedListener/CharacterScreen_MainButton.hpp"
#include "../inheritedListener/CharacterScreen_CharacterButton.hpp"
#include "ScreenManager.hpp"

namespace graphics {

	CharacterScreen::CharacterScreen() : m_playerSelected(NULL) {
		load();
	}

	CharacterScreen::~CharacterScreen() {
		delete m_leftContainer;
		delete m_characterContainer;
		delete m_leftButtonContainer;
		delete m_newCharButton;
		delete m_returnButton;
		delete m_rightContainer;
		delete m_upButtonContainer;
		delete m_rightMainContainer;
		delete m_statButton;
		delete m_skillButton;
		delete m_launchButton;
	}

	void CharacterScreen::load() {

		m_leftContainer = new Container();
		m_leftContainer->setBackground("ressources/gui/background_characterFrame.png", full);
		this->add(m_leftContainer);

		m_characterContainer = new Container();
		m_leftContainer->add(m_characterContainer);

		m_leftButtonContainer = new Container();
		m_leftButtonContainer->setLayout(new VerticalFixedLayout(VerticalFixedLayout::full, VerticalFixedLayout::fixed));
		m_leftButtonContainer->setBackground("ressources/gui/background_characterFrameDown.png", full);
		m_leftContainer->add(m_leftButtonContainer);

		m_leftContainer->setLayout(new SplitFixedLayout(SplitFixedLayout::horizontal, SplitFixedLayout::second, 120));



		m_newCharButton = new Button("New Character", GUIStyle::button());
		m_newCharButton->setSize(200, 50);
		m_newCharButton->addListener(new CharacterScreen_MainButton(this));
		m_leftButtonContainer->add(m_newCharButton);

		m_returnButton = new Button("Return", GUIStyle::button());
		m_returnButton->setSize(200, 50);
		m_returnButton->addListener(new CharacterScreen_MainButton(this));
		m_leftButtonContainer->add(m_returnButton);


		m_rightContainer = new Container();
		this->add(m_rightContainer);
		this->setLayout(new SplitFixedLayout(SplitFixedLayout::vertical, SplitFixedLayout::first, 250));


		m_characterContainer->setLayout(new VerticalFixedLayout(VerticalFixedLayout::fixed, VerticalFixedLayout::full));

		CharacterFrame* charSelect = NULL;
		for(int i=0; i<game::PlayerList::size(); i++) {
			CharacterFrame* cf = new CharacterFrame(game::PlayerList::get(i));
			m_characterContainer->add(cf);
			m_chars.push_back(cf);
			if(game::CurrentCharacter::get() == game::PlayerList::get(i)) {
				charSelect = cf;
			}
			cf->addListener(new CharacterScreen_CharacterButton(this));
		}

		m_upButtonContainer = new Container();
		m_rightContainer->add(m_upButtonContainer);

		m_rightMainContainer = new Container();
		m_rightMainContainer->setBackgroundColor(sf::Color(30, 30, 30));
		m_rightContainer->add(m_rightMainContainer);

		m_rightContainer->setLayout(new SplitFixedLayout(SplitFixedLayout::horizontal, SplitFixedLayout::first, 80));
		m_upButtonContainer->setBackground("ressources/gui/background1.png", full);
		m_upButtonContainer->setLayout(new HorizontalFixedLayout(HorizontalFixedLayout::full, HorizontalFixedLayout::fixed));


		m_statButton = new Button("Statistic", GUIStyle::button());
		m_statButton->setSize(150, 50);
		m_statButton->addListener(new CharacterScreen_MainButton(this));
		m_statButton->setEnable(false);
		m_upButtonContainer->add(m_statButton);

		m_skillButton = new Button("Skill", GUIStyle::button());
		m_skillButton->setSize(150, 50);
		m_skillButton->addListener(new CharacterScreen_MainButton(this));
		m_skillButton->setEnable(false);
		m_upButtonContainer->add(m_skillButton);

		m_launchButton = new Button("Launch", GUIStyle::button());
		m_launchButton->setSize(150, 50);
		m_launchButton->addListener(new CharacterScreen_MainButton(this));
		m_launchButton->setEnable(false);
		m_upButtonContainer->add(m_launchButton);
		if(charSelect != NULL)
			characterChanged(charSelect);

		if(game::PlayerList::size() == 0) {
			network::Packet packet(network::Network::getSocket(), network::PacketType::SESSION_ASKCHARACTER);
			packet.send();
		}

	}

	std::string CharacterScreen::getComponentName() {
		return "CharacterScreen";
	}

	std::string CharacterScreen::getName() {
		return "CharacterScreen";
	}

	void CharacterScreen::characterChanged(void* origin) {
		for(boost::ptr_vector<CharacterFrame>::iterator it = m_chars.begin(); it != m_chars.end(); ++it) {
			it->setSelect(false);
		}
		((CharacterFrame*)origin)->setSelect(true);
		m_playerSelected = ((CharacterFrame*)origin)->getPlayer();
		viewChanged(m_statButton);
		m_statButton->setSelected(true, true);
		m_statButton->setEnable(true);
		m_skillButton->setSelected(false, true);
		m_skillButton->setEnable(true);
		m_launchButton->setSelected(false, true);
		m_launchButton->setEnable(true);
		game::CurrentCharacter::set(m_playerSelected);
	}

	void CharacterScreen::viewChanged(void* origin) {
		if(m_playerSelected != NULL && origin == m_statButton) {
			Container* tmp = new CharacterInfo(m_playerSelected);
			m_rightContainer->replace(m_rightMainContainer, tmp);
			delete m_rightMainContainer;
			m_rightMainContainer = tmp;
			((CharacterInfo*)m_rightMainContainer)->load();

		}
		else if(m_playerSelected != NULL && origin == m_skillButton) {
			Container* tmp = new CharacterSkill(m_playerSelected);
			m_rightContainer->replace(m_rightMainContainer, tmp);
			delete m_rightMainContainer;
			m_rightMainContainer = tmp;
			((CharacterSkill*)m_rightMainContainer)->load();

		}
		else if(m_playerSelected != NULL && origin == m_launchButton) {
			m_window->setContentPane(ScreenManager::gameList());
		}
		else if(origin == m_newCharButton) {
			m_window->setContentPane(ScreenManager::newCharacter());
		}
		else if(origin == m_returnButton) {
			m_window->setContentPane(ScreenManager::connection());
			network::Network::close();
			m_characterContainer->clear();
			m_chars.clear();
			game::CurrentCharacter::reset();
			game::PlayerList::clear();
		}
	}

	void CharacterScreen::refreshCharacter() {
		//clear
		m_characterContainer->clear();
		m_chars.clear();

		for(int i=0; i<game::PlayerList::size(); i++) {
			CharacterFrame* cf = new CharacterFrame(game::PlayerList::get(i));
			m_characterContainer->add(cf);
			m_chars.push_back(cf);
			if(game::CurrentCharacter::get() == game::PlayerList::get(i)) {
				characterChanged(cf);
			}
			cf->addListener(new CharacterScreen_CharacterButton(this));
		}


	}
}


