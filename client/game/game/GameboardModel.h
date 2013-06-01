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
#include "../character/Player.hpp"
#include "Case.h"


namespace game {

	class GameboardModel {
	public:
		~GameboardModel();

		//getters
		//static boost::ptr_vector<Player> getVectorOTherPlayer();
		static int getHeight();
		static int getWidth();
		static int getIdMode();
		static int getScoreTeam(int i);

		//setters
		static void setMode(int idMode);
		static void setScore(int scoreTeam1, int scoreTeam2);

		//gameboard
		static Case*** getGameboard(int i);

		//IO manage
		static void read(std::string path);

	private:

		GameboardModel();

		int m_widthGameBoard, m_heightGameBoard, m_idMode, m_scoreTeam1, m_scoreTeam2;
		Case*** m_gameboard;	//1rst Layer
		Case*** m_gameboardLayer;	//2nd Layer
		static GameboardModel* getInstance();
		static boost::shared_ptr<GameboardModel> m_instance;
	};

} /* namespace game */
#endif /* GAMEBOARDMODEL_H_ */
