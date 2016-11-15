/*
 * Chat.hpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#ifndef CHAT_HPP_
#define CHAT_HPP_

#include <boost/ptr_container/ptr_vector.hpp>
#include "Packet.hpp"
#include "PacketType.hpp"
#include "../client/Client.hpp"

class Chat {

public:
	Chat(network::PacketType::PacketContents type);
	~Chat();
	void set(network::PacketType::PacketContents type);
	int getID();
	void addClient(Client* client);
	void removeClient(Client* client);
	bool isClient(Client* client);
	void sendAll(network::Packet packet);
	void send(std::string message);

private:
	int m_id;
	boost::ptr_vector<Client> m_clients;
	network::PacketType::PacketContents m_type;
};


#endif /* CHAT_HPP_ */
