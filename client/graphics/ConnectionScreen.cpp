/*
 * ConnectionScreen.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#include "ConnectionScreen.hpp"
#include "InheritedListener/ConnectionScreen_Button.hpp"

namespace graphics {

	ConnectionScreen::ConnectionScreen(Window* window) : m_window(window) {

	}

	void ConnectionScreen::load() {
		this->setLayout(new CenterLayout());

		Container* c2 = new Container();
		c2->setLayout(new PassivLayout());
		c2->setSize(300, 300);
		this->add(c2);

		Label* l1 = new Label("Pseudo : ", GUIStyle::label());
		l1->setSize(200, 40);
		l1->setCoord(util::Coordinates(50, 20));
		c2->add(l1);

		TextField* tf1 = new TextField(GUIStyle::textfield());
		tf1->setSize(200, 50);
		tf1->setCoord(util::Coordinates(50, 60));
		c2->add(tf1);

		Label* l2 = new Label("Password : ", GUIStyle::label());
		l2->setSize(200, 40);
		l2->setCoord(util::Coordinates(50, 120));
		c2->add(l2);

		TextField* tf2 = new TextField(GUIStyle::textfield());
		tf2->setSize(200, 50);
		tf2->setCoord(util::Coordinates(50, 160));
		c2->add(tf2);

		m_bConnection = new Button("Connection", GUIStyle::button());
		m_bConnection->setSize(200, 50);
		m_bConnection->setCoord(util::Coordinates(50, 220));
		m_bConnection->addListener(new ConnectionScreen_Button(this));
		c2->add(m_bConnection);

	}

	void ConnectionScreen::startConnection() {

		InnerWindow* w1 = new InnerWindow("login...", 300, 100, GUIStyle::innerwindow());
		w1->setCloseable(false);
		this->add(w1);
		w1->setWidthCenter();
		w1->setHeightCenter();

		Label* l3 = new Label("Connection... ", GUIStyle::label());
		l3->setAlign(Label::alignCenter);
		l3->setSize(200, 40);
		l3->setCoord(util::Coordinates(0, 0));
		w1->add(l3);

		m_bConnection->setEnable(false);

		boost::this_thread::sleep(boost::posix_time::milliseconds(500));
		l3->setText("Receive information...");
		boost::this_thread::sleep(boost::posix_time::milliseconds(500));
		l3->setText("Loggin in !");
		boost::this_thread::sleep(boost::posix_time::milliseconds(500));
		CharacterScreen* characterScreen = new CharacterScreen(m_window);
		m_window->setContentPane(characterScreen);
		characterScreen->load();
	}

};


