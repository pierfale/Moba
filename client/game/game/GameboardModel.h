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
		static boost::ptr_vector<Player> getVectorOTherPlayer();
		static int getHeight();
		static int getWidth();

		//gameboard
		static Case*** getGameboard(int i);

		//IO manage
		static void read(std::string path);

	private:

		GameboardModel();

		int m_widthGameBoard, m_heightGameBoard;
		Case*** m_gameboard;	//1rst Layer
		Case*** m_gameboardLayer;	//2nd Layer
		static GameboardModel* getInstance();
		static boost::shared_ptr<GameboardModel> m_instance;
	};

} /* namespace game */
#endif /* GAMEBOARDMODEL_H_ */
