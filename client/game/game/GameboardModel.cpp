/*
 * GameboardModel.cpp
 *
 *  Created on: 19 avr. 2013
 *      Author: Béni
 */

#include "GameboardModel.h"

namespace game {

	boost::shared_ptr<GameboardModel> GameboardModel::m_instance;

	GameboardModel::GameboardModel() : m_widthGameBoard(0) , m_heightGameBoard(0) {
		m_player = NULL;
		m_gameboard = NULL;
		m_gameboardLayer = NULL;
	}
	GameboardModel::~GameboardModel() {
		for (int i = 0 ; i < m_heightGameBoard ; i++ ) {
			delete[](getInstance()->m_gameboardLayer[i]);
			delete[](getInstance()->m_gameboard[i]);
		}
		delete(getInstance()->m_gameboardLayer);
		delete(getInstance()->m_gameboard);
	}

	//getters
	Player* GameboardModel::getClientPlayer() { return getInstance()->m_player; }
	Player* GameboardModel::getOtherPlayer(int i) {return &(getInstance()->m_oPlayers).at(i);}
	boost::ptr_vector<Player> GameboardModel::getVectorOTherPlayer() {return getInstance()->m_oPlayers;}
	int GameboardModel::getHeight() { return getInstance()->m_heightGameBoard; }
	int GameboardModel::getWidth() { return getInstance()->m_widthGameBoard; }
	Case*** GameboardModel::getGameboard(int i){
		if (i == 0) return getInstance()->m_gameboard;
		else return getInstance()->m_gameboardLayer;
	}

	//setters
	void GameboardModel::setClientPlayer(Player* player) {getInstance()->m_player=player;}

	//vector manage
	void GameboardModel::addPlayer(Player* p){getInstance()->m_oPlayers.push_back(p);}
	void GameboardModel::removePlayer(Player* p) {}
	void GameboardModel::removeAllPlayer(Player* p) {}

	//singleton pattern
	GameboardModel* GameboardModel::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new GameboardModel());
		return m_instance.get();
	}

	//IO manage
		void GameboardModel::read(std::string path) {
			if (path=="") return ;
			int width, height;
			std::ifstream f(path.c_str(), std::ios::in | std::ios::binary);
			if (!f) log_err "cannot open file " + path end_log_err;
			f.read((char*) &width, sizeof(int));
			f.read((char*) &height, sizeof(int));
			getInstance()->m_widthGameBoard = width; getInstance()->m_heightGameBoard = height;
			getInstance()->m_gameboard = (Case***)malloc(getInstance()->m_widthGameBoard*sizeof(Case**));
			getInstance()->m_gameboardLayer = (Case***)malloc(getInstance()->m_widthGameBoard*sizeof(Case**));
			for (int i = 0 ; i < getInstance()->m_heightGameBoard ; i++ ) {
				getInstance()->m_gameboard[i] = (Case**)malloc(getInstance()->m_heightGameBoard*sizeof(Case*));
				getInstance()->m_gameboardLayer[i] = (Case**)malloc(getInstance()->m_heightGameBoard*sizeof(Case*));
			}

			int idtmp;
			for (int i = 0 ; i < getInstance()->m_heightGameBoard ; i++){
				for (int j = 0 ; j < getInstance()->m_widthGameBoard ; j++){
					f.read((char*) &idtmp, sizeof(int));
					getInstance()->m_gameboard[j][i] = new Case(idtmp);
					if (idtmp == 23) {getInstance()->m_gameboard[j][i]->setPassable(false);
					}
				}
			}
			f.close();

			std::ifstream g((path+"L").c_str(), std::ios::in | std::ios::binary);
			for (int i = 0 ; i < getInstance()->m_heightGameBoard ; i++){
				for (int j = 0 ; j < getInstance()->m_widthGameBoard ; j++){
					g.read((char*) &idtmp, sizeof(int));
					getInstance()->m_gameboardLayer[j][i] = new Case(idtmp);
				}
			}
			g.close();
		}

} /* namespace game */
