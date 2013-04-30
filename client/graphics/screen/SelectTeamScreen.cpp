/*
 * SelectTeamScreen.cpp
 *
 *  Created on: 19 avr. 2013
 *      Author: pierre
 */

#include "SelectTeamScreen.hpp"
#include "../inheritedListener/SelectTeamScreen_MainButton.hpp"
#include "ScreenManager.hpp"

namespace graphics {

	SelectTeamScreen::SelectTeamScreen(game::Game* game) : m_game(game) {
		load();
	}

	SelectTeamScreen::~SelectTeamScreen() {
		delete m_buttonContainer;
		delete m_buttonUpContainer;
		delete m_buttonDownContainer;
		delete m_mainContainer;
		delete m_mainUpContainer;
		delete m_mainDownContainer;
		delete m_chatLabelStyle;
		delete m_chatLabel;
		delete m_chatTextField;
		delete m_changeTeamButton;
		delete m_launchButton;
		delete m_returnButton;

	}

	void SelectTeamScreen::load() {

		m_buttonContainer = new Container();
		m_buttonContainer->setBackground("ressources/gui/background_characterFrame.png", full);
		this->add(m_buttonContainer);

		m_buttonUpContainer = new Container();
		m_buttonUpContainer->setLayout(new VerticalFixedLayout(VerticalFixedLayout::fixed, VerticalFixedLayout::fixed));
		m_buttonContainer->add(m_buttonUpContainer);

		m_buttonDownContainer = new Container();
		m_buttonDownContainer->setLayout(new VerticalFixedLayout(VerticalFixedLayout::full, VerticalFixedLayout::fixed));
		m_buttonContainer->add(m_buttonDownContainer);

		m_buttonContainer->setLayout(new SplitFixedLayout(SplitFixedLayout::horizontal, SplitFixedLayout::second, 60));

		m_mainContainer = new Container();
		m_mainContainer->setBackgroundColor(sf::Color(30, 30, 30));
		this->add(m_mainContainer);

		this->setLayout(new SplitFixedLayout(SplitFixedLayout::vertical, SplitFixedLayout::first, 250));

		m_changeTeamButton = new Button("Change Team", GUIStyle::button());
		m_changeTeamButton->setSize(200, 50);
		m_changeTeamButton->addListener(new SelectTeamScreen_MainButton(this));
		m_buttonUpContainer->add(m_changeTeamButton);

		m_launchButton = new Button("Launch", GUIStyle::button());
		m_launchButton ->setSize(200, 50);
		m_launchButton ->addListener(new SelectTeamScreen_MainButton(this));
		m_launchButton->setEnable(false);
		m_buttonUpContainer->add(m_launchButton);

		m_returnButton = new Button("Return", GUIStyle::button());
		m_returnButton->setSize(200, 50);
		m_returnButton->addListener(new SelectTeamScreen_MainButton(this));
		m_buttonDownContainer->add(m_returnButton);

		m_mainUpContainer = new Container();
		m_mainContainer->add(m_mainUpContainer);

		m_mainDownContainer = new Container();
		m_mainContainer->add(m_mainDownContainer);

		m_mainContainer->setLayout(new SplitFixedLayout(SplitFixedLayout::horizontal, SplitFixedLayout::first, 500));

		m_team1Container = new Container();
		m_team1Container->setBackground("ressources/gui/background_characterFrame.png", none);
		m_team1Container->setLayout(new VerticalFixedLayout(VerticalFixedLayout::fixed, VerticalFixedLayout::full));
		m_mainUpContainer->add(m_team1Container);

		m_team2Container = new Container();
		m_team2Container->setBackground("ressources/gui/background_characterFrame.png", none);
		m_team2Container->setLayout(new VerticalFixedLayout(VerticalFixedLayout::fixed, VerticalFixedLayout::full));
		m_mainUpContainer->add(m_team2Container);

		m_mainUpContainer->setLayout(new HorizontalLayout());

		m_chatLabelStyle = new BasicStyle();
		m_chatLabel = new Label("yoyo", m_chatLabelStyle);
		m_mainDownContainer->add(m_chatLabel);

		m_chatTextField = new TextField(GUIStyle::textfield());
		m_mainDownContainer->add(m_chatTextField);

		m_mainDownContainer->setLayout(new SplitFixedLayout(SplitFixedLayout::horizontal, SplitFixedLayout::second, 40));
	}

	std::string SelectTeamScreen::getComponentName() {
		return "SelectTeamScreen";
	}
	std::string SelectTeamScreen::getName() {
		return "SelectTeamScreen";
	}

	void SelectTeamScreen::refreshPlayer() {
		m_team1Container->clear();
		m_team2Container->clear();
		m_chars.clear();

		for(int i=0; i<game::GamePlayerList::size(); i++) {
			CharacterFrame* cf = new CharacterFrame(game::GamePlayerList::get(i));
			m_chars.push_back(cf);
			if(game::GamePlayerList::get(i)->getTeam() == 1)
				m_team1Container->add(cf);
			else
				m_team2Container->add(cf);
			if(game::GamePlayerList::get(i)->getID() == game::CurrentCharacter::get()->getID()
					&& m_game->getCreator() == game::GamePlayerList::get(i)->getName())
				m_launchButton->setEnable(true);
		}
	}

	void SelectTeamScreen::buttonPressed(void* origin) {
		if(origin == m_returnButton) {
			m_window->setContentPane(ScreenManager::gameList());
			network::Packet packet(network::Network::getSocket(), network::PacketType::SESSION_ASKQUITGAME);
			packet.send();
		}
		else if(origin == m_changeTeamButton) {
			network::Packet packet(network::Network::getSocket(), network::PacketType::SESSION_ASKCHANGETEAM);
			packet.send();
		}
		else if(origin == m_launchButton) {
			network::Packet packet(network::Network::getSocket(), network::PacketType::SESSION_ASKLAUNCHGAME);
			packet.send();
		}
	}

}


