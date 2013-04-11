/*
 * Gameboard.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: Béni
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "../ImageLoader.hpp"
#include "Gameboard.h"

namespace graphics {

	//standard
	Gameboard::Gameboard(std::string path) : Component(), m_widthGameBoard(0) , m_heightGameBoard(0), m_path(path) , m_cam() , m_loaded(false) {
		m_gameboard = NULL; m_gameboardLayer = NULL; m_spriteOfGameBoard = NULL; m_texture = NULL; m_player = NULL;
	}
	Gameboard::~Gameboard() {
		for (int i = 0 ; i < m_heightGameBoard ; i++ ) {
			delete[](m_gameboardLayer[i]);
			delete[](m_gameboard[i]);
		}
		delete(m_gameboardLayer);
		delete(m_gameboard);
		free(m_spriteOfGameBoard);
	}
	std::string Gameboard::toString() {return "GameBoard \n H = "+util::Cast::intToString(m_heightGameBoard)+"\n W = "+util::Cast::intToString(m_widthGameBoard);}

	//init
	void Gameboard::load(Player* p) {
		m_window->getImageLoader()->add("ressources/game/Tiles.png");
		m_texture = m_window->getImageLoader()->get("ressources/game/Tiles.png");
		m_spriteOfGameBoard = new sf::Sprite();
		m_gameboard = NULL;
		m_player = p;
		m_player->load(m_window);
		for(boost::ptr_vector<Player>::iterator it = m_oPlayers.begin(); it != m_oPlayers.end(); ++it) {
			it->load(m_window);
		}
		read(m_path);
		m_loaded = true;
	}

	//graphics manage
	void Gameboard::draw(sf::RenderWindow* render) {
		std::cout << "drawing" << std::endl;
		if (!m_loaded) return;

		int stepX = 1, stepY = 1;
		if (m_cam.getCoord().x+(m_width/50) == m_widthGameBoard) stepX = 0;
		if (m_cam.getCoord().y+(m_height/50) == m_heightGameBoard) stepY = 0;

		for (int i = m_cam.getCoord().y, k = 0 ; i < m_cam.getCoord().y+((m_height/50)+stepY) ; i++, k++){
			for (int j = m_cam.getCoord().x , l = 0; j < m_cam.getCoord().x+((m_width/50)+stepX) ; j++, l++){
				//1rst Layer
				std::cout << i << std::endl;
				std::cout << j << std::endl;
				if (m_gameboard[j][i]->getId() != 0) {
					m_spriteOfGameBoard->setTexture(*m_texture);std::cout << "setTexture" << std::endl;
					sf::Rect<int> spriteZone((m_gameboard[j][i]->getId()*50)%200,((m_gameboard[j][i]->getId()*50)/200)*50,50,50);std::cout << "create Rect" << std::endl;
					m_spriteOfGameBoard->setTextureRect(spriteZone);std::cout << "setTextureRect" << std::endl;
					m_spriteOfGameBoard->setPosition(l*50,k*50);std::cout << "setPosition" << std::endl;
					render->draw(*m_spriteOfGameBoard);std::cout << "drawn" << std::endl;
				}
				//2nd Layer
				if (m_gameboardLayer[j][i]->getId() != 0) {
					m_spriteOfGameBoard->setTexture(*m_texture);std::cout << "setTexture" << std::endl;
					sf::Rect<int> spriteZone((m_gameboardLayer[j][i]->getId()*50)%200,((m_gameboardLayer[j][i]->getId()*50)/200)*50,50,50);std::cout << "create Rect" << std::endl;
					m_spriteOfGameBoard->setTextureRect(spriteZone);std::cout << "setTextureRect" << std::endl;
					m_spriteOfGameBoard->setPosition(l*50,k*50);std::cout << "setPosition" << std::endl;
					render->draw(*m_spriteOfGameBoard);std::cout << "drawn" << std::endl;
				}
			}
		}
		// Camera
		drawCamera(render);
		//Client player
		if (m_player->getOnMove()) m_player->incFrame();
		if (m_player->getCoordinates().x >= m_cam.getCoord().x && m_player->getCoordinates().x <= m_cam.getCoord().x+((m_width/50)+stepX)
				&& m_player->getCoordinates().y >= m_cam.getCoord().y && m_player->getCoordinates().y <= m_cam.getCoord().y+((m_height/50)+stepY))
			drawPlayer(render, m_player);
		//Others Players
		for(boost::ptr_vector<Player>::iterator p = m_oPlayers.begin(); p != m_oPlayers.end(); ++p) {
			if (p->getOnMove()) p->incFrame();
			if (p->getCoordinates().x >= m_cam.getCoord().x && p->getCoordinates().x <= m_cam.getCoord().x+((m_width/50)+stepX)
					&& p->getCoordinates().y >= m_cam.getCoord().y && p->getCoordinates().y <= m_cam.getCoord().y+((m_height/50)+stepY))
				drawPlayer(render, &(*p));
		}
	}

	void Gameboard::drawCamera(sf::RenderWindow* render){
		m_spriteOfGameBoard->setTexture(*m_texture);
		sf::Rect<int> spriteZone(150,0,10,10);
		m_spriteOfGameBoard->setTextureRect(spriteZone);
		m_spriteOfGameBoard->setPosition(0,0);
		render->draw(*m_spriteOfGameBoard);
	}

	void Gameboard::drawPlayer(sf::RenderWindow* render, Player* current){
		current->getSprite()->setTexture(*current->getTexture());
		sf::Rect<int> spriteZone(50*current->getFrame(),85*current->getDirection(),50,85);
		current->getSprite()->setTextureRect(spriteZone);
		current->getSprite()->setPosition((-m_cam.getCoord().x+current->getCoordinates().x)*50,
				(-m_cam.getCoord().y+current->getCoordinates().y)*50);
		render->draw(*(current->getSprite()));
	}

	bool Gameboard::event(sf::Event* event, bool used) {
		m_cam.event(event, &m_width ,&m_height);
		for(boost::ptr_vector<Player>::iterator it = m_oPlayers.begin(); it != m_oPlayers.end(); ++it) {
			it->event(event);
		}
		return used;
	}

	void Gameboard::validate() {}

	//vector manage
	void Gameboard::addPlayer(Player* p) {m_oPlayers.push_back(p);}
	void Gameboard::removePlayer(Player* p) {}

	//IO manage
	void Gameboard::read(std::string path) {
		if (path=="") return ;

		std::ifstream f(path.c_str(), std::ios::in | std::ios::binary);
		f.read((char*) &m_widthGameBoard, sizeof(int));
		f.read((char*) &m_heightGameBoard, sizeof(int));

		m_cam.setLandMark(m_widthGameBoard, m_heightGameBoard);

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

	void Gameboard::write(std::string path) {
		std::ofstream f( path.c_str() , std::ios::out | std::ios::binary);
		int h,w, in;
		if(!f.is_open()) { std::cout << "Failed to open the file" << std::endl; }
		else {
			std::cout << "height?"<< std::endl;
			std::cin >> h;
			f.write((char *)&h, sizeof(int));
			std::cout << "width?"<< std::endl;
			std::cin >> w;
			f.write((char *)&w, sizeof(int));
			for (int j = 0 ; j < h ; j++) {
				for (int i = 0 ; i < w ; i++){
					std::cout << util::Cast::intToString(i)+":"+util::Cast::intToString(j) << std::endl;
					std::cin >> in;
					if ( in < 0) { --i; std::cout << "wrong value" << std::endl; }
					else { f.write((char *)&in, sizeof(int)); }
				}
			}
		}
		f.close();
	}

	void Gameboard::full() {
		std::ofstream f( "ressources/game/mapOfArena" , std::ios::out | std::ios::binary);
		int in = 100, tmp = 0;
		if(!f.is_open()) { std::cout << "Failed to open the file" << std::endl; }
		else {
			f.write((char *)&in, sizeof(int));
			f.write((char *)&in, sizeof(int));
			in = 1;
			for (int j = 0 ; j < 100 ; j++) {
				for (int i = 0 ; i < 100 ; i++){
					f.write((char *)&in, sizeof(int));
				}
			}
		}
		f.close();
		in = 0;
		srand (time(NULL));
		std::ofstream g( "ressources/game/mapOfArenaL" , std::ios::out | std::ios::binary);
		if(!g.is_open()) { std::cout << "Failed to open the file" << std::endl; }
		else {
			for (int j = 0 ; j < 100 ; j++) {
				for (int i = 0 ; i < 100 ; i++){
					in = 0; tmp = rand() % 100 + 1;
					if ( i == 0 ) in = 8;
					else if ( i == 99) in = 9;
					else if ( j == 0 ) in = 4;
					else if ( j == 99) in = 5;
					else if ( i == 0 && j == 0 ) in = 6;
					else if ( i == 99 && j == 0) in = 7 ;
					else if ( i == 0 && j == 99) in = 10;
					else if ( i == 99 && j == 99) in = 11;
					else if (tmp > 90) in = 23;
					g.write((char *)&in, sizeof(int));
				}
			}
		}
		g.close();
	}

} /* namespace graphics */
