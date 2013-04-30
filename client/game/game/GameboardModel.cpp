/*
 * GameboardModel.cpp
 *
 *  Created on: 19 avr. 2013
 *      Author: Béni
 */

#include "GameboardModel.h"

namespace game {

	GameboardModel::GameboardModel(Player* player, std::string path) : m_widthGameBoard(0) , m_heightGameBoard(0) {
		m_player = player;
		m_gameboard = NULL;
		m_gameboardLayer = NULL;
		read(path);
	}
	GameboardModel::~GameboardModel() {
		for (int i = 0 ; i < m_heightGameBoard ; i++ ) {
			delete[](m_gameboardLayer[i]);
			delete[](m_gameboard[i]);
		}
		delete(m_gameboardLayer);
		delete(m_gameboard);
	}

	//getters
	Player* GameboardModel::getClientPlayer() { return m_player; }
	Player* GameboardModel::getOtherPlayer(int i) {return &m_oPlayers.at(i);}
	boost::ptr_vector<Player> GameboardModel::getVectorOTherPlayer() {return m_oPlayers;}
	int GameboardModel::getHeight() { return m_heightGameBoard; }
	int GameboardModel::getWidth() { return m_widthGameBoard; }
	Case*** GameboardModel::getGameboard(int i){
		if (i == 0) return m_gameboard;
		else return m_gameboardLayer;
	}

	//vector manage
	void GameboardModel::addPlayer(Player* p){m_oPlayers.push_back(p);}
	void GameboardModel::removePlayer(Player* p) {}
	void GameboardModel::removeAllPlayer(Player* p) {}


	//IO manage
		void GameboardModel::read(std::string path) {
			if (path=="") return ;

			std::ifstream f(path.c_str(), std::ios::in | std::ios::binary);
			f.read((char*) &m_widthGameBoard, sizeof(int));
			f.read((char*) &m_heightGameBoard, sizeof(int));

			m_gameboard = (Case***)malloc(m_widthGameBoard*sizeof(Case**));
			m_gameboardLayer = (Case***)malloc(m_widthGameBoard*sizeof(Case**));
			for (int i = 0 ; i < m_heightGameBoard ; i++ ) {
				m_gameboard[i] = (Case**)malloc(m_heightGameBoard*sizeof(Case*));
				m_gameboardLayer[i] = (Case**)malloc(m_heightGameBoard*sizeof(Case*));
			}

			int idtmp;
			for (int i = 0 ; i < m_heightGameBoard ; i++){
				for (int j = 0 ; j < m_widthGameBoard ; j++){
					f.read((char*) &idtmp, sizeof(int));
					m_gameboard[j][i] = new Case(idtmp);
					if (idtmp == 23) m_gameboard[i][j]->setPassable(false);
				}
			}
			f.close();

			std::ifstream g((path+"L").c_str(), std::ios::in | std::ios::binary);
			for (int i = 0 ; i < m_heightGameBoard ; i++){
				for (int j = 0 ; j < m_widthGameBoard ; j++){
					g.read((char*) &idtmp, sizeof(int));
					m_gameboardLayer[j][i] = new Case(idtmp);
				}
			}
			g.close();
		}

} /* namespace game */
