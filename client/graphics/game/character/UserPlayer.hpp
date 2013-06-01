/*
 * UserPlayer.hpp
 *
 *  Created on: 7 mai 2013
 *      Author: pierre
 */

#ifndef GRAPHICS_USERPLAYER_HPP_
#define GRAPHICS_USERPLAYER_HPP_

#include "Player.hpp"

namespace graphics {

	class UserPlayer : public Player {

	public:
		UserPlayer(game::Player* model);
		bool event(sf::Event* event, Camera* cam, bool used);
		void update();
		void checkTarget();
		void updateCoord();
		void checkMovement();
		void moveTo(util::CoordInt goal);
		void setState(int state);

		void draw(sf::RenderWindow* render, Camera* cam);

	private:
		util::CoordInt m_nextDest;
		util::CoordInt m_lastDest;

	};
}


#endif /* USERPLAYER_HPP_ */
