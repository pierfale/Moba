/*
 * CharacterSkill_SkillListener.hpp
 *
 *  Created on: 25 mai 2013
 *      Author: pierre
 */

#ifndef CHARACTERSKILL_SKILLLISTENER_HPP_
#define CHARACTERSKILL_SKILLLISTENER_HPP_

#include "../listener/ButtonListener.hpp"
#include "../inheritedComponent/CharacterSkill.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class CharacterSkill_SkillListener : public ButtonListener {


	public:
		CharacterSkill_SkillListener(CharacterSkill* view);
		void pressed(void* origin);

	private:
		CharacterSkill* m_view;
	};


}


#endif /* CHARACTERSKILL_SKILLLISTENER_HPP_ */
