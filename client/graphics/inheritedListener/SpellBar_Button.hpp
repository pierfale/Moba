/*
 * SpellBar_Button.hpp
 *
 *  Created on: 28 mai 2013
 *      Author: pierre
 */

#ifndef SPELLBAR_BUTTON_HPP_
#define SPELLBAR_BUTTON_HPP_

#include "../listener/ButtonListener.hpp"
#include "../game/ui/SpellBarr.h"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class SpellBar_Button : public ButtonListener {

	public:
		SpellBar_Button(SpellBarr* view);
		void pressed(void* origin);

	private:
		SpellBarr* m_view;
	};


}



#endif /* SPELLBAR_BUTTON_HPP_ */
