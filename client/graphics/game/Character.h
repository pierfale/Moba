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
#include <SFML/Graphics.hpp>

#include "../../util/Coordinates.hpp"
#include "../Component/ComponentInclude.hpp"
#include "Camera.h"
#include "../../game/character/Player.hpp"

#define CHARACTER_SIZE_X 50
#define CHARACTER_SIZE_Y 85
#define CHARACTER_TIME_BETWEEN_FRAME 0.01
#define CHARACTER_DIAG_RATIO 0.7
#define CASE_SIZE 50

namespace graphics {

class Character {
	public:
		enum Direction{SOUTH, WEST, EAST, NORTH};

		Character(game::Player* model);
		bool event(sf::Event* event, Camera* cam, bool used, bool isPlayer);

		void draw(sf::RenderWindow* render, Camera* cam);
		game::Player* getModel();
		void setDirection(Direction dir);
		void checkMovement();
		void updateCoord();
		void calculCoord();

	private:
		game::Player* m_model;
		util::CoordInt nextDest;
		util::CoordInt lastDest;
		boost::timer m_timer;
		sf::Texture* m_texture;
		sf::Sprite m_sprite;

		Direction m_direction;

		int m_nbFrame;
		float m_nextFrame;
		bool m_onMove;
		network::PacketType::PacketContents m_lastServDir;
		int m_nDirection;
		bool m_focus;

	};

} /* namespace graphics */
#endif /* CHARACTER_H_ */
