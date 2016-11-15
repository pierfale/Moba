/*
 * Game.hpp
 *
 *  Created on: 22 avr. 2013
 *      Author: pierre
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <boost/ptr_container/ptr_vector.hpp>
#include <string>
#include <map>
#include <utility>
#include "mode/GameMode.hpp"
#include "GameCreate.hpp"
#include "GameCreateList.hpp"
#include "../client/Client.hpp"

class Game {

public:
	Game(GameMode* mode);
	Game(GameMode* mode, GameCreate* game);

	int getID();
	int playerSize();
	std::map<Player*, Client*>* getClientMap();
	Client* getPlayerByID(int id);
	void setClient(int id, Client* client);
	void checkPlayerReady();
	void sendAll(network::Packet packet);
	void sendAllOther(network::Packet packet, Client* client);
	void run();
	void end();
	GameMode* getMode();
	Chat* getChat();

private:
	int m_id;
	GameMode* m_mode;
	std::map<Player*, Client*> m_clients;
	Chat* m_chat;

};


#endif /* GAME_HPP_ */
