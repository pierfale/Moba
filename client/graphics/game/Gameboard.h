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
#include <algorithm>

#include "boost/ptr_container/ptr_vector.hpp"

#include "../ImageLoader.hpp"
#include "../component/Component.hpp"
#include "../../game/game/Case.h"
#include "../../game/game/GamePlayerList.hpp"
#include "../../game/menu/CurrentCharacter.hpp"
#include "Camera.h"
#include "../../game/game/GameboardModel.h"
#include "character/Player.hpp"
#include "character/UserPlayer.hpp"
#include "animation/Animation.hpp"
#include "BufferDraw.hpp"

#define SIZE_TILE 50

namespace graphics {

class UserInterface;

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
		static util::CoordInt convertCoord(util::CoordInt coord);
		static util::CoordFloat convertCoord(util::CoordFloat coord);

		//animation
		static void addAnimation(Animation* animation);
		static void removeAnimation(Animation* animation);

	private:
		sf::Texture* m_texture;
		static Camera m_cam;
		boost::ptr_vector<Player> m_players; //graphics Other Players
		UserInterface* m_interface;
		static boost::ptr_vector<Animation> m_animations;
		BufferDraw m_bufferY;
		bool m_loaded;
	};

} /* namespace graphics */
#endif /* GAMEBOARD_H_ */
