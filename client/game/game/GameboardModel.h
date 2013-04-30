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

#include <boost/shared_ptr.hpp>
#include "boost/ptr_container/ptr_vector.hpp"
#include "Case.h"
#include "../character/Player.hpp"

namespace game {

	class GameboardModel {
	public:
		virtual ~GameboardModel();

		//getters
		static Player* getClientPlayer();
		static Player* getOtherPlayer(int i);
		static boost::ptr_vector<Player> getVectorOTherPlayer();
		static int getHeight();
		static int getWidth();

		//setters
		static void setClientPlayer(Player* player);

		//vector manage
		static void addPlayer(Player* p);
		static void removePlayer(Player* p);
		static void removeAllPlayer(Player* p);

		//gameboard
		static Case*** getGameboard(int i);

		//IO manage
		static void read(std::string path);

	private:

		GameboardModel();

		int m_widthGameBoard, m_heightGameBoard;
		Case*** m_gameboard;	//1rst Layer
		Case*** m_gameboardLayer;	//2nd Layer
		boost::ptr_vector<Player> m_oPlayers; //Other Player
		Player* m_player; //Client Player

		static GameboardModel* getInstance();
		static boost::shared_ptr<GameboardModel> m_instance;
	};

} /* namespace game */
#endif /* GAMEBOARDMODEL_H_ */
