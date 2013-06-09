/*
 * Chat.cpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#include "Chat.hpp"
#include "../inheritedListener/Chat_Listener.hpp"
#include "Packet.hpp"
#include "../../network/Network.hpp"


namespace graphics {

	Chat::Chat(int type) : m_id(0) {
		m_scroll = new ScrollBar(GUIStyle::scrollbar());
		this->add(m_scroll);

		m_labelStyle = new BasicStyle();
		m_label = new Label("", m_labelStyle);
		m_label->setVAlign(Label::valignTop);
		m_label->setMinimalSize();
		m_scroll->setContentPane(m_label);

		m_botContainer = new Container();
		this->add(m_botContainer);


		m_textField = new TextField(GUIStyle::textfield());
		m_textField->addListener(new Chat_TextFieldListener(this));
		m_botContainer->add(m_textField);

	if(type != 1) {
		m_button = new Button("Send", GUIStyle::button());
		m_button->addListener(new Chat_ButtonListener(this));
		m_button->setEnable(false);
		m_botContainer->add(m_button);
	}
	else
		m_button = NULL;

		if(type != 1)
			m_botContainer->setLayout(new SplitFixedLayout(SplitFixedLayout::vertical, SplitFixedLayout::second, 150));

		this->setLayout(new SplitFixedLayout(SplitFixedLayout::horizontal, SplitFixedLayout::second, 40));
	}

	Chat::~Chat() {
		delete m_scroll;
		delete m_labelStyle;
		delete m_label;
		delete m_botContainer;
		delete m_textField;
		if(m_button != NULL)
			delete m_button;
	}

	void Chat::setID(int id) {
		m_id = id;
		if(m_button != NULL)
		m_button->setEnable(true);
	}

	int Chat::getID() {


		return m_id;
	}

	void Chat::send(void* origin) {
		if(m_textField->getText() != "" && m_id != 0) {
			network::Packet packet(network::Network::getSocket(), network::PacketType::CHAT_SENDMESSAGE);
			packet << m_id << m_textField->getText();
			packet.send();
			m_textField->setText("");
		}
	}

	void Chat::receive(std::string message) {
		m_label->setText(m_label->getText()+message+'\n');
		m_label->setMinimalSize();
		m_scroll->setScrollDown();
	}


}


