/*
 * SelectTeamScreen.cpp
 *
 *  Created on: 19 avr. 2013
 *      Author: pierre
 */

#include "SelectTeamScreen.hpp"

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
		m_buttonUpContainer->add(m_changeTeamButton);

		m_returnButton = new Button("Return", GUIStyle::button());
		m_returnButton->setSize(200, 50);
		m_buttonDownContainer->add(m_returnButton);

		m_mainUpContainer = new Container();
		m_mainContainer->add(m_mainUpContainer);

		m_mainDownContainer = new Container();
		m_mainContainer->add(m_mainDownContainer);

		m_mainContainer->setLayout(new SplitFixedLayout(SplitFixedLayout::horizontal, SplitFixedLayout::first, 500));

		m_chatLabelStyle = new BasicStyle();
		m_chatLabel = new Label("yoyo", m_chatLabelStyle);
		m_mainDownContainer->add(m_chatLabel);

		m_chatTextField = new TextField(GUIStyle::textfield());
		m_mainDownContainer->add(m_chatTextField);

		m_mainDownContainer->setLayout(new SplitFixedLayout(SplitFixedLayout::horizontal, SplitFixedLayout::second, 40));
	}
}


