/*
 * Gameboard.h
 *
 *  Created on: 8 avr. 2013
 *      Author: Béni
 */

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include "Case.h"
#include "../component/Component.hpp"
#include <string>
#include "Camera.h"
#include "boost/ptr_container/ptr_vector.hpp"
#include "Player.h"

namespace graphics {

	class Gameboard : public Component{
	public:
		//standard
		Gameboard(std::string="");
		virtual ~Gameboard();
		std::string toString();

		//init
		void load(Player* p);

		//graphics manage
		void draw(sf::RenderWindow* render);
		void drawCamera(sf::RenderWindow* render);
		void drawPlayer(sf::RenderWindow* render, Player* player);
		bool event(sf::Event* event, bool used);
		void validate();

		//vector manage
		void addPlayer(Player* p);
		void removePlayer(Player* p);
		void removeAllPlayer(Player* p);

		//IO manage
		void read(std::string path);
		static void write(std::string path);
		static void full();

	private:
		Case*** m_gameboard;	//1rst Layer
		Case*** m_gameboardLayer;	//2nd Layer
		int m_widthGameBoard, m_heightGameBoard;
		sf::Sprite* m_spriteOfGameBoard;
		std::string m_path;
		sf::Texture* m_texture;
		Camera m_cam;
		bool m_loaded;
		boost::ptr_vector<Player> m_oPlayers;	//Other Player
		Player* m_player;	//Client Player
	};

} /* namespace graphics */
#endif /* GAMEBOARD_H_ */
