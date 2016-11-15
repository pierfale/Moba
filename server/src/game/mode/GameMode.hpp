/*
 * GameMode.hpp
 *
 *  Created on: 28 avr. 2013
 *      Author: pierre
 */

#ifndef GAMEMODE_HPP_
#define GAMEMODE_HPP_

#include "../../client/Client.hpp"

class Game;

class GameMode {

public:
	virtual ~GameMode();
	void setGame(Game* game);
	virtual void init() = 0;
	virtual void start() = 0;
	virtual bool run() = 0;
	virtual void end() = 0;
	virtual void dead(Client* client, Player* killer) = 0;
	std::string getMap();

protected:
	Game* m_game;
	std::string m_map;
	int m_id;

};


#endif /* GAMEMODE_HPP_ */
