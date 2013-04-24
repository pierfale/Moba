/*
 * CreateGameScreen.cpp
 *
 *  Created on: 23 avr. 2013
 *      Author: pierre
 */

#include "CreateGameScreen.hpp"
#include "ScreenManager.hpp"
#include "../inheritedListener/CreateGameScreen_DownButton.hpp"

namespace graphics {

	CreateGameScreen::CreateGameScreen() {
		load();
	}

	CreateGameScreen::~CreateGameScreen() {
		delete m_upContainer;
		delete m_downContainer;
		delete m_downPseudoContainer;
		delete m_downButtonContainer;
		delete m_nameTextField;
		delete m_returnButton;
		delete m_createButton;
	}

	void CreateGameScreen::load() {
		m_upContainer = new Container();
		this->add(m_upContainer);

		m_downContainer = new Container();
		m_downContainer->setBackground("ressources/gui/background1.png", full);
		this->add(m_downContainer);

		this->setLayout(new SplitFixedLayout(SplitFixedLayout::horizontal, SplitFixedLayout::second, 100));

		m_downPseudoContainer = new Container();
		m_downPseudoContainer->setLayout(new CenterLayout());
		m_downContainer->add(m_downPseudoContainer);

		m_downButtonContainer = new Container();
		m_downButtonContainer->setLayout(new HorizontalFixedLayout(HorizontalFixedLayout::full, HorizontalFixedLayout::fixed));
		m_downContainer->add(m_downButtonContainer);

		m_nameTextField = new TextField(GUIStyle::textfield());
		m_nameTextField->setSize(200, 50);
		m_downPseudoContainer->add(m_nameTextField);

		m_returnButton = new Button("Return", GUIStyle::button());
		m_returnButton->setSize(200, 50);
		m_returnButton->addListener(new CreateGameScreen_DownButton(this));
		m_downButtonContainer->add(m_returnButton);

		m_createButton = new Button("Create", GUIStyle::button());
		m_createButton->setSize(200, 50);
		m_createButton->addListener(new CreateGameScreen_DownButton(this));
		m_downButtonContainer->add(m_createButton);

	}

	void CreateGameScreen::buttonChanged(void* origin) {
		if(origin == m_createButton && m_nameTextField->getText() != "") {

			network::Packet packet(network::Network::getSocket(), network::PacketType::SESSION_CREATEGAME);
			packet <<m_nameTextField->getText();
			packet.send();

			m_window->setContentPane(ScreenManager::gameList());

		}
		else if(origin == m_returnButton) {
			m_window->setContentPane(ScreenManager::gameList());
		}
	}

}
