/*
 * CharacterInfo.hpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#ifndef CHARACTERINFO_HPP_
#define CHARACTERINFO_HPP_

#include "../component/ComponentInclude.hpp"
#include "../layout/LayoutInclude.hpp"
#include "../../game/character/Player.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class CharacterInfo : public Container {

	public:
		CharacterInfo(game::Player* player);
		void load();

	private:
		game::Player* m_player;

	};

}


#endif /* CHARACTERINFO_HPP_ */
