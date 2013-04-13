/*
 * CharacterFrame.hpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#ifndef CHARACTERFRAME_HPP_
#define CHARACTERFRAME_HPP_

#include "../component/Button.hpp"
#include "../../game/character/Player.hpp"

namespace graphics {

	class CharacterFrame : public Button {

	public:
		CharacterFrame(game::Player* player);
		void draw(sf::RenderWindow* render);
		void setSelect(bool state);
		bool isSelectable();
		game::Player* getPlayer();
	private:
		game::Player* m_player;
		bool m_select;
	};

}

#endif /* CHARACTERFRAME_HPP_ */
