/*
 * GameboardModel.h
 *
 *  Created on: 19 avr. 2013
 *      Author: Béni
 */

#ifndef GAMEBOARDMODEL_H_
#define GAMEBOARDMODEL_H_

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "boost/ptr_container/ptr_vector.hpp"
#include "Case.h"
#include "../character/Player.hpp"

namespace game {

	class GameboardModel {
	public:
		GameboardModel(Player* player, std::string path);
		virtual ~GameboardModel();

		//getters
		Player* getClientPlayer();
		Player* getOtherPlayer(int i);
		boost::ptr_vector<Player> getVectorOTherPlayer();
		int getHeight();
		int getWidth();

		//vector manage
		void addPlayer(Player* p);
		void removePlayer(Player* p);
		void removeAllPlayer(Player* p);

		//gameboard
		Case*** getGameboard(int i);

		//IO manage
		void read(std::string path);

	private:
		int m_widthGameBoard, m_heightGameBoard;
		Case*** m_gameboard;	//1rst Layer
		Case*** m_gameboardLayer;	//2nd Layer
		boost::ptr_vector<Player> m_oPlayers; //Other Player
		Player* m_player; //Client Player
	};

} /* namespace game */
#endif /* GAMEBOARDMODEL_H_ */
