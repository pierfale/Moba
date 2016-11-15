/*
 * GameCreate.hpp
 *
 *  Created on: 22 avr. 2013
 *      Author: pierre
 */

#ifndef GAMECREATE_HPP_
#define GAMECREATE_HPP_

#include <boost/ptr_container/ptr_vector.hpp>
#include <string>
#include "../client/Client.hpp"
#include "../chat/Chat.hpp"
#include "../chat/ChatList.hpp"

class GameCreate {

public:
	GameCreate(std::string name, Client* creator);
	~GameCreate();
	int getID();
	std::string getName();
	Client* getCreator();
	Chat* getChat();
	void addPlayer(Client* player);
	bool removePlayer(Client* player);
	void sendAll(network::Packet packet);
	int playerSize();
	Client* getPlayer(int i);

private:
	int m_id;
	std::string m_name;
	Client* m_creator;
	Chat* m_chat;
	boost::ptr_vector<Client> m_clients;
};


#endif /* GAMECREATE_HPP_ */
