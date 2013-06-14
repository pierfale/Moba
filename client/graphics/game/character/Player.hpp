/*
 * Player.hpp
 *
 *  Created on: 7 mai 2013
 *      Author: pierre
 */

#ifndef GRAPHICS_PLAYER_HPP_
#define GRAPHICS_PLAYER_HPP_

#include "Character.hpp"
#include "../../../game/character/Player.hpp"
#include "../../../game/game/CurrentSpell.hpp"
#include "../../Cursor.hpp"

namespace graphics {

	class Player : public Character {

	public:
		Player(game::Player* model);
		virtual ~Player();
		bool event(sf::Event* event, Camera* cam, bool used);
		virtual void update();
		virtual void updateCoord();

	protected:
		boost::timer m_lastAttack;

	};
}


#endif /* PLAYER_HPP_ */
