/*
 * Player.h
 *
 *  Created on: 10 avr. 2013
 *      Author: Béni
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"
#include <string>

namespace graphics {

	class Player : public Character{
	public:
		Player(std::string name);
		virtual ~Player();

		void event(sf::Event* event);

		void moveTo(int x, int y);
		void setTarget(int x, int y);

	};

} /* namespace graphics */
#endif /* PLAYER_H_ */
