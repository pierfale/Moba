/*
 * Chat.cpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#include "Chat.hpp"
#include "ChatList.hpp"

Chat::Chat(network::PacketType::PacketContents type) {
	m_id = ChatList::getNextID();
	m_type = type;
}

Chat::~Chat() {
	while(m_clients.size() > 0)
		m_clients.release(m_clients.begin()).release();
}

void Chat::set(network::PacketType::PacketContents type) {
	m_type = type;
	for(unsigned int i=0; i<m_clients.size(); i++) {
		network::Packet answer(m_clients.at(i).getSocket(), network::PacketType::CHAT_CREATECHAT);
		answer << m_id << m_type;
		answer.send();
	}
}

int Chat::getID() {
	return m_id;
}

void Chat::addClient(Client* client) {
	m_clients.push_back(client);
	send(client->getCharacter()->getName()+" enter in room");
	network::Packet answer(client->getSocket(), network::PacketType::CHAT_CREATECHAT);
	answer << m_id << m_type;
	answer.send();
}

void Chat::removeClient(Client* client) {
	for(boost::ptr_vector<Client>::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
		std::cout << "REMOVE : " << client << " => " << "-" << &(*it) << std::endl;
		if(&(*it) == client) {
			m_clients.release(it).release();
			send(client->getCharacter()->getName()+" quit room");
			return;
		}
	}
}

bool Chat::isClient(Client* client) {
	for(boost::ptr_vector<Client>::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
		if(&(*it) == client)
			return true;
	}
	return false;
}

void Chat::sendAll(network::Packet packet) {
	for(boost::ptr_vector<Client>::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
		it->send(packet);
	}
}

void Chat::send(std::string message) {
	network::Packet answer(NULL, network::PacketType::CHAT_RECEIVEMESSAGE);
	answer << m_id << "<color=255,215,0><size=16>"+message+"</size></color>";
	sendAll(answer);
}


