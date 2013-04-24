/*
 * GameListScreen.cpp
 *
 *  Created on: 16 avr. 2013
 *      Author: pierre
 */

#include "GameListScreen.hpp"
#include "../inheritedListener/GameListScreen_MainButton.hpp"
#include "../inheritedListener/GameListScreen_Table.hpp"
#include "ScreenManager.hpp"

namespace graphics {

	GameListScreen::GameListScreen() {
		load();
		m_gameSelected = NULL;
	}

	GameListScreen::~GameListScreen() {
		delete m_buttonContainer;
		delete m_buttonUpContainer;
		delete m_buttonDownContainer;
		delete m_mainContainer;
		delete m_matchmakingButton;
		delete m_joinButton;
		delete m_createButton;
		delete m_returnButton;
		delete m_table;
		delete m_tableStyle;
	}

	void GameListScreen::load() {
		network::Packet packet(network::Network::getSocket(), network::PacketType::SESSION_ASKGAME);
		packet.send();

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

		m_matchmakingButton = new Button("Matchmaking", GUIStyle::button());
		m_matchmakingButton->setSize(200, 50);
		m_matchmakingButton->addListener(new GameListScreen_MainButton(this));
		m_buttonUpContainer->add(m_matchmakingButton);

		m_joinButton = new Button("Join Game", GUIStyle::button());
		m_joinButton->setSize(200, 50);
		m_joinButton->addListener(new GameListScreen_MainButton(this));
		m_joinButton->setEnable(false);
		m_buttonUpContainer->add(m_joinButton);

		m_createButton = new Button("Create Game", GUIStyle::button());
		m_createButton->setSize(200, 50);
		m_createButton->addListener(new GameListScreen_MainButton(this));
		m_buttonUpContainer->add(m_createButton);

		m_returnButton = new Button("Return", GUIStyle::button());
		m_returnButton->setSize(200, 50);
		m_returnButton->addListener(new GameListScreen_MainButton(this));
		m_buttonDownContainer->add(m_returnButton);

		std::vector<std::string> columns;
		columns.push_back("Name");
		columns.push_back("Creator");
		columns.push_back("Players");
		m_table = new Table(columns, GUIStyle::table());
		m_mainContainer->add(m_table);
		m_table->addListener(new GameListScreen_Table(this));
		m_table->setColumnsWidth(2, 100);

		m_tableStyle = new BasicStyle();
		m_tableStyle->setFontColor(sf::Color::White);

		for(int i=0; i<game::GameList::size(); i++) {
			int id = m_table->addRow();
			Label* gName = new Label(game::GameList::get(i)->getName(), m_tableStyle);
			gName->setAlign(Label::alignCenter);
			m_table->set(id, 0, gName);
			Label* gCreator = new Label(game::GameList::get(i)->getCreator(), m_tableStyle);
			gCreator->setAlign(Label::alignCenter);
			m_table->set(id, 1, gCreator);
			Label* gPlayer = new Label("0/0", m_tableStyle);
			gPlayer->setAlign(Label::alignCenter);
			m_table->set(id, 2, gPlayer);
			m_table->setValueOnRow(id, game::GameList::get(i));
		}
	}

	std::string GameListScreen::getComponentName() {
		return "GameListScreen";
	}

	std::string GameListScreen::getName() {
		return "GameListScreen";
	}

	void GameListScreen::buttonPressed(void* origin) {
		if(origin == m_returnButton) {
			m_window->setContentPane(ScreenManager::character());
		}
		else if(origin == m_joinButton && m_gameSelected != NULL) {
			m_window->setContentPane(ScreenManager::selectTeam(m_gameSelected));
		}
		else if(origin == m_createButton) {
			m_window->setContentPane(ScreenManager::createGameScreen());
		}
	}

	void GameListScreen::gameChanged(void* origin) {
		m_gameSelected = (game::Game*)m_table->getValueOnRow(m_table->getSelectedRow());
		if(m_gameSelected != NULL) {
			m_joinButton->setEnable(true);
		}
		else
			m_joinButton->setEnable(false);
	}

	void GameListScreen::refreshGame() {
		m_table->removeAllRow();
		/*
		for(int i=0; i<game::GameList::size(); i++) {
			int id = m_table->addRow();
			Label* gName = new Label(game::GameList::get(i)->getName(), m_tableStyle);
			gName->setAlign(Label::alignCenter);
			m_table->set(id, 0, gName);
			Label* gCreator = new Label(game::GameList::get(i)->getCreator(), m_tableStyle);
			gCreator->setAlign(Label::alignCenter);
			m_table->set(id, 1, gCreator);
			Label* gPlayer = new Label("0/0", m_tableStyle);
			gPlayer->setAlign(Label::alignCenter);
			m_table->set(id, 2, gPlayer);
			m_table->setValueOnRow(id, game::GameList::get(i));
		}*/
	}
}


