/*
 * Character.h
 *
 *  Created on: 8 avr. 2013
 *      Author: Béni
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>
#include <queue>
#include <math.h>

#include "SFML/Graphics.hpp"
#include "../../util/Coordinates.hpp"
#include "../Component/ComponentInclude.hpp"
#include "Camera.h"
#include "../../game/character/Player.hpp"

namespace graphics {

class Character {
	public:

		enum Direction{SOUTH, WEST, EAST, NORTH};

		Character(game::Player* player);
		virtual ~Character();

		//graphics manage
		void load(Window* window);
		void event(sf::Event* event, Camera cam, bool client);
		void moveTo();
		void setTarget(int x, int y);
		void incFrame();
		void draw(sf::RenderWindow* render, Camera cam);

		//getters
		int getDirection();
		sf::Sprite* getSprite();
		sf::Texture* getTexture();
		int getFrame();
		bool getOnMove();
		game::Player* getPlayerModel();

		//setters
		void setDirection(int dir);

		//pathfinding
		std::vector<util::CoordInt> getPathAs();

	protected:
		int m_nbFrame;
		bool m_onMove;
		Direction m_direction;
		util::CoordFloat m_target;
		sf::Texture* m_texture;
		boost::timer m_frame;
		game::Player* m_player;
		sf::Sprite* m_sprite;
	};

} /* namespace graphics */
#endif /* CHARACTER_H_ */
