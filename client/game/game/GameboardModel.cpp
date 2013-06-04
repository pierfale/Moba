/*
 * GameboardModel.cpp
 *
 *  Created on: 19 avr. 2013
 *      Author: Béni
 */

#include "GameboardModel.h"

namespace game {

boost::shared_ptr<GameboardModel> GameboardModel::m_instance;

GameboardModel::GameboardModel() : m_widthGameBoard(0) , m_heightGameBoard(0), m_idMode(-1), m_scoreTeam1(0), m_scoreTeam2(0)  {
	m_gameboard = NULL;
	m_gameboardLayer = NULL;
}


GameboardModel::~GameboardModel() {
	for (int j = 0 ; j < m_heightGameBoard ; j++) {
		for (int k = 0 ; k < m_widthGameBoard ; k++) {
			delete getInstance()->m_gameboard[j][k];
			delete getInstance()->m_gameboardLayer[j][k];
		}
	}
	for (int i = 0 ; i < m_heightGameBoard ; i++ ) {
		free(getInstance()->m_gameboardLayer[i]);
		free(getInstance()->m_gameboard[i]);
	}
	free(getInstance()->m_gameboardLayer);
	free(getInstance()->m_gameboard);
}

//setters
void GameboardModel::setMode(int idMode) {getInstance()->m_idMode = idMode;}
void GameboardModel::setScore(int scoreTeam1, int scoreTeam2) {
	getInstance()->m_scoreTeam1 = scoreTeam1;
	getInstance()->m_scoreTeam2 = scoreTeam2;
}

//getters
int GameboardModel::getHeight() { return getInstance()->m_heightGameBoard; }
int GameboardModel::getWidth() { return getInstance()->m_widthGameBoard; }
Case*** GameboardModel::getGameboard(int i){
	if (i == 0) return getInstance()->m_gameboard;
	else return getInstance()->m_gameboardLayer;
}
int GameboardModel::getIdMode() { return getInstance()->m_idMode; }
int GameboardModel::getScoreTeam(int i) {
	if (i == 1) return getInstance()->m_scoreTeam1 ;
	else return getInstance()->m_scoreTeam2;
}

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
	getInstance()->m_widthGameBoard = width;
	getInstance()->m_heightGameBoard = height;
	getInstance()->m_gameboard = (Case***)malloc(getInstance()->m_widthGameBoard*sizeof(Case**));
	getInstance()->m_gameboardLayer = (Case***)malloc(getInstance()->m_widthGameBoard*sizeof(Case**));
	for (int i = 0 ; i < getInstance()->m_heightGameBoard ; i++ ) {
		getInstance()->m_gameboard[i] = (Case**)malloc(getInstance()->m_heightGameBoard*sizeof(Case*));
		getInstance()->m_gameboardLayer[i] = (Case**)malloc(getInstance()->m_heightGameBoard*sizeof(Case*));
	}
	int idtmp;
	for (int y = 0 ; y < getInstance()->m_heightGameBoard ; y++){
		for (int x = 0 ; x < getInstance()->m_widthGameBoard ; x++){
			f.read((char*) &idtmp, sizeof(int));
			getInstance()->m_gameboard[x][y] = new Case(idtmp);
			std::cout << getInstance()->m_gameboard[x][y]->getId();
			if (idtmp == 3) {getInstance()->m_gameboard[x][y]->setPassable(false);
			}
		}
		std::cout << std::endl;
	}
	for (int y = 0 ; y < getInstance()->m_heightGameBoard ; y++){
		for (int x = 0 ; x < getInstance()->m_widthGameBoard ; x++){
			f.read((char*) &idtmp, sizeof(int));
			getInstance()->m_gameboardLayer[x][y] = new Case(idtmp);
			std::cout << getInstance()->m_gameboardLayer[x][y]->getId();
		}
		std::cout << std::endl;
	}
	f.close();
}

} /* namespace game */
