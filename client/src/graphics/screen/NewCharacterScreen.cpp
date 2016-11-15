/*
 * NewCharacterScreen.cpp
 *
 *  Created on: 15 avr. 2013
 *      Author: pierre
 */

#include "NewCharacterScreen.hpp"
#include "ScreenManager.hpp"
#include "../inheritedListener/NewCharacterScreen_DownButton.hpp"

namespace graphics {

	NewCharacterScreen::NewCharacterScreen() {
		load();
	}

	NewCharacterScreen::~NewCharacterScreen() {
		delete m_upContainer;
		delete m_downContainer;
		delete m_downPseudoContainer;
		delete m_downButtonContainer;
		delete m_pseudoTextField;
		delete m_returnButton;
		delete m_createButton;
	}

	void NewCharacterScreen::load() {
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

		m_pseudoTextField = new TextField(GUIStyle::textfield());
		m_pseudoTextField->setSize(200, 50);
		m_downPseudoContainer->add(m_pseudoTextField);

		m_returnButton = new Button("Return", GUIStyle::button());
		m_returnButton->setSize(200, 50);
		m_returnButton->addListener(new NewCharacterScreen_DownButton(this));
		m_downButtonContainer->add(m_returnButton);

		m_createButton = new Button("Create", GUIStyle::button());
		m_createButton->setSize(200, 50);
		m_createButton->addListener(new NewCharacterScreen_DownButton(this));
		m_downButtonContainer->add(m_createButton);

	}

	void NewCharacterScreen::buttonChanged(void* origin) {
		if(origin == m_createButton && m_pseudoTextField->getText() != "") {
			m_window->setContentPane(ScreenManager::character());
			network::Packet packet(network::Network::getSocket(), network::PacketType::SESSION_CREATECHARACTER);
			packet << m_pseudoTextField->getText();
			packet.send();
		}
		else if(origin == m_returnButton) {
			m_window->setContentPane(ScreenManager::character());
		}
	}
}


