/*
 * ConnectionScreen.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#include "ConnectionScreen.hpp"
#include "../InheritedListener/ConnectionScreen_Button.hpp"
#include "ScreenManager.hpp"

namespace graphics {

	ConnectionScreen::ConnectionScreen() {
		load();
		m_messageInnerWindow = NULL;
		m_messageLabel = NULL;
	}

	ConnectionScreen::~ConnectionScreen() {
		delete m_mainContainer;
		delete m_pseudoLabel;
		delete m_pseudoTextField;
		delete m_passwordLabel;
		delete m_passwordTextField;
		if(m_messageInnerWindow != NULL) {
			delete m_messageInnerWindow;
			delete m_messageLabel;
		}
	}

	void ConnectionScreen::load() {
		this->setBackground("ressources/gui/background_title.jpg", none);

		m_mainContainer = new Container();
		m_mainContainer->setLayout(new PassivLayout());
		m_mainContainer->setBackground("ressources/gui/background_frame_title.png", none);
		add(m_mainContainer);

		m_pseudoLabel = new Label("Pseudo : ", GUIStyle::label());
		m_pseudoLabel->setSize(200, 40);
		m_pseudoLabel->setCoord(util::CoordInt(50, 20));
		m_mainContainer->add(m_pseudoLabel);

		m_pseudoTextField = new TextField(GUIStyle::textfield());
		m_pseudoTextField->setSize(200, 50);
		m_pseudoTextField->setCoord(util::CoordInt(50, 60));
		m_mainContainer->add(m_pseudoTextField);

		m_passwordLabel = new Label("Password : ", GUIStyle::label());
		m_passwordLabel->setSize(200, 40);
		m_passwordLabel->setCoord(util::CoordInt(50, 120));
		m_mainContainer->add(m_passwordLabel);

		m_passwordTextField = new TextField(GUIStyle::textfield());
		m_passwordTextField->setSize(200, 50);
		m_passwordTextField->setCoord(util::CoordInt(50, 160));
		m_passwordTextField->setHide(true);
		m_mainContainer->add(m_passwordTextField);

		m_connectionButton = new Button("Connection", GUIStyle::button());
		m_connectionButton->setSize(200, 50);
		m_connectionButton->setCoord(util::CoordInt(50, 220));
		m_connectionButton->addListener(new ConnectionScreen_Button(this));
		m_mainContainer->add(m_connectionButton);

		this->setLayout(new CenterLayout());
		m_mainContainer->setSize(300, 300);

		//Tmp
		m_pseudoTextField->setText("test");
		m_passwordTextField->setText("test");
	}

	std::string ConnectionScreen::getComponentName() {
		return "ConnectionScreen";
	}

	std::string ConnectionScreen::getName() {
		return "ConnectionScreen";
	}

	bool ConnectionScreen::event(sf::Event* event, bool used) {
		if(event->type == sf::Event::MouseButtonPressed && !used && m_messageInnerWindow != NULL) {
			this->remove(m_messageInnerWindow);
			m_connectionButton->setEnable(true);
			used = true;
			delete m_messageInnerWindow;
			delete m_messageLabel;
			m_messageInnerWindow = NULL;
			m_messageLabel = NULL;
		}
		return Container::event(event, used);
	}

	void ConnectionScreen::startConnection() {

		m_messageInnerWindow = new InnerWindow("login...", 300, 100, GUIStyle::innerwindow());
		m_messageInnerWindow->setCloseable(false);
		this->add(m_messageInnerWindow);
		m_messageInnerWindow->setWidthCenter();
		m_messageInnerWindow->setHeightCenter();

		m_messageLabel = new Label("Connection... ", GUIStyle::label());
		m_messageLabel->setAlign(Label::alignCenter);
		m_messageLabel->setCoord(util::CoordInt(0, 0));
		m_messageLabel->setMinimalSize();
		m_messageInnerWindow->add(m_messageLabel);
		m_messageInnerWindow->setMinimalSize();
		m_connectionButton->setEnable(false);

		if(m_pseudoTextField->getText() == "" || m_passwordTextField->getText() == "") {
			m_messageLabel->setText("Please enter a pseudo/password");
		}
		else {
			//hash
			boost::uuids::detail::sha1 s;
			std::string hex;
			char hash[20];
			s.process_bytes(m_passwordTextField->getText().c_str(), m_passwordTextField->getText().size());
			unsigned int digest[5];
			s.get_digest(digest);
			for(int i = 0; i < 5; ++i) {
				const char* tmp = reinterpret_cast<char*>(digest);
				hash[i*4] = tmp[i*4+3];
				hash[i*4+1] = tmp[i*4+2];
				hash[i*4+2] = tmp[i*4+1];
				hash[i*4+3] = tmp[i*4];
			}
			std::stringstream ss;
			ss << std::hex;
			for(int i = 0; i < 20; ++i)
			{
				ss << ((hash[i] & 0x000000F0) >> 4)
					<< (hash[i] & 0x0000000F);
			}
			log_out "Connection to "+Config::get("server")+":"+Config::get("port") end_log_out;
			if(network::Network::init(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(Config::get("server")), util::Cast::stringToInt(Config::get("port"))))) {
				network::Packet packet(network::Network::getSocket(), network::PacketType::SESSION_ASKCONNECTION);
				packet << m_pseudoTextField->getText() << ss.str();
				packet.send();
			}

		}
	}

	void ConnectionScreen::setMessage(std::string message) {
		if(m_messageLabel != NULL) {
			m_messageLabel->setText(message);
			m_messageLabel->setMinimalSize();
			m_messageInnerWindow->setMinimalSize();
		}
		else {
			m_messageInnerWindow = new InnerWindow("login...", 300, 100, GUIStyle::innerwindow());
			m_messageInnerWindow->setCloseable(false);
			this->add(m_messageInnerWindow);
			m_messageInnerWindow->setWidthCenter();
			m_messageInnerWindow->setHeightCenter();

			m_messageLabel = new Label(message, GUIStyle::label());
			m_messageLabel->setAlign(Label::alignCenter);
			m_messageLabel->setCoord(util::CoordInt(0, 0));
			m_messageLabel->setMinimalSize();
			m_messageInnerWindow->add(m_messageLabel);
			m_messageInnerWindow->setMinimalSize();
		}
	}

	void ConnectionScreen::setConnected() {
		m_window->setContentPane(ScreenManager::character());
	}

};


