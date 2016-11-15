/*
 * GameCreate.cpp
 *
 *  Created on: 22 avr. 2013
 *      Author: pierre
 */

#include "GameCreate.hpp"
#include "GameCreateList.hpp"

GameCreate::GameCreate(std::string name, Client* creator) : m_name(name), m_creator(creator) {
	m_id = GameCreateList::getNextID();
	m_chat = new Chat(network::PacketType::CHAT_SELECTTEAM);
	ChatList::add(m_chat);
	log_out "New CreateGame : ID="+util::Cast::intToString(m_id)+", name="+name+", creator="+m_creator->getCharacter()->getName()+"["+m_creator->getPseudo()+"]" end_log_out;
}

GameCreate::~GameCreate() {
	while(m_clients.size() > 0) {
		m_clients.release(m_clients.begin()).release();
	}
}

int GameCreate::getID() {
	return m_id;
}

std::string GameCreate::getName() {
	return m_name;
}

Client* GameCreate::getCreator() {
	return m_creator;
}

void GameCreate::addPlayer(Client* player) {
	m_clients.push_back(player);
}

Chat* GameCreate::getChat() {
	return m_chat;
}

bool GameCreate::removePlayer(Client* player) {
	for(boost::ptr_vector<Client>::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
		if(&(*it) == player) {
			m_clients.release(it).release();
			m_chat->removeClient(player);
			if(player == m_creator)
				return true;
			return false;
		}
	}
	return false;
}

int GameCreate::playerSize() {
	return m_clients.size();
}

Client* GameCreate::getPlayer(int i) {
	return &m_clients.at(i);
}

void GameCreate::sendAll(network::Packet packet) {
	for(boost::ptr_vector<Client>::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
		it->send(packet);
	}
}
