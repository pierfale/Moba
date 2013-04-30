/*
 * Gameboard.h
 *
 *  Created on: 8 avr. 2013
 *      Author: Béni
 */

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "boost/ptr_container/ptr_vector.hpp"

#include "../ImageLoader.hpp"
#include "../component/Component.hpp"
#include "../../game/game/Case.h"
#include "Camera.h"
#include "../../game/game/GameboardModel.h"
#include "Character.h"
#include "animation/Animation.h"
#include "ui/UserInterface.h"

#define SIZE_TILE 50

namespace graphics {

	class Gameboard : public Container{
	public:
		//standard
		Gameboard();
		virtual ~Gameboard();

		//graphics manage
		void draw(sf::RenderWindow* render);
		void drawGameboard(sf::RenderWindow* render, game::Case*** gameboard);
		bool event(sf::Event* event, bool used);
		void validate();
		static void loadImage();

	private:
		sf::Texture* m_texture;
		Camera m_cam;
		bool m_loaded;
		Character* m_player; //graphics Client Player
		boost::ptr_vector<Character> m_oPlayers; //graphics Other Players
		UserInterface* m_interface;
	};

} /* namespace graphics */
#endif /* GAMEBOARD_H_ */
