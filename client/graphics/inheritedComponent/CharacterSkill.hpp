/*
 * CharacterSkill.hpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#ifndef CHARACTERSKILL_HPP_
#define CHARACTERSKILL_HPP_

#include "../component/ComponentInclude.hpp"
#include "../inheritedComponent/ButtonImage.hpp"
#include "../layout/LayoutInclude.hpp"
#include "../../game/character/Player.hpp"
#include "../../game/skill/Skill.hpp"
#include "../../game/skill/SkillReader.hpp"

namespace graphics {

	class CharacterSkill : public Container {

	public:
		CharacterSkill(game::Player* player);
		void load();

	private:
		game::Player* m_player;

	};

}


#endif /* CHARACTERSKILL_HPP_ */
