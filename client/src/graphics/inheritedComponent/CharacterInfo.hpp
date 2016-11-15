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
#include "Packet.hpp"
#include "../../network/Network.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class CharacterInfo : public Container {

	public:
		CharacterInfo(game::Player* player);
		~CharacterInfo();
		void load();
		void refresh();

		std::string getComponentName();
		static std::string getName();

	private:
		game::Player* m_player;
		BasicStyle* m_labelstyle;
		Label* m_name;
		Label* m_life;
		Label* m_mana;
		Label* m_physicalAttack;
		Label* m_magicalAttack;
		Label* m_physicalArmor;
		Label* m_magicalArmor;
		Label* m_attackSpeed;
		Label* m_speed;

	};

}


#endif /* CHARACTERINFO_HPP_ */
