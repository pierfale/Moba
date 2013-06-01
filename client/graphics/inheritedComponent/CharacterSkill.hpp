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
#include "Packet.hpp"
#include "../../network/Network.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class CharacterSkill : public Container {

	public:
		CharacterSkill(game::Player* player);
		~CharacterSkill();
		void load();
		std::string getComponentName();
		static std::string getName();

		void setActiveSkill(int id);
		void skillPressed(void* origin);


	private:
		void checkDisableSkill();
		game::Player* m_player;
		std::map<int, ButtonImage*> m_button;
		std::map<ButtonImage*, int> m_buttonReverse;
		boost::ptr_vector<Line>  m_line;

	};

}


#endif /* CHARACTERSKILL_HPP_ */
