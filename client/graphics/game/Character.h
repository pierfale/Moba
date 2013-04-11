/*
 * Character.h
 *
 *  Created on: 8 avr. 2013
 *      Author: Béni
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "../component/Component.hpp"
#include <string>
#include "../../util/Coordinates.hpp"

namespace graphics {

class Character {
	public:

		enum Direction{SOUTH, WEST, EAST, NORTH};

		Character(std::string name);
		virtual ~Character();

		std::string toString();

		//graphics manage
		void load(Window* window);
		virtual void event(sf::Event* event) = 0;
		virtual void moveTo(int x, int y) = 0;
		virtual void setTarget(int x, int y) = 0;
		void incFrame();

		//getters
		int getDirection();
		sf::Sprite* getSprite();
		sf::Texture* getTexture();
		int getFrame();
		util::Coordinates getCoordinates();
		bool getOnMove();

		//setters
		void setCoord(int x, int y);
		void setDirection(int dir);

		//pathfinding
		std::vector<util::Coordinates> getPathAs();

	protected:
		std::string m_name;
		int m_nbFrame;
		bool m_onMove;
		Direction m_direction;
		util::Coordinates m_coord, m_target;
		sf::Sprite* m_sprite;
		sf::Texture* m_texture;
		std::vector<util::Coordinates> path;
	};

} /* namespace graphics */
#endif /* CHARACTER_H_ */
