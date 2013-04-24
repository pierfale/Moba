/*
 * CharacterScreen_CharacterButton.hpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#ifndef CHARACTERSCREEN_CHARACTERBUTTON_HPP_
#define CHARACTERSCREEN_CHARACTERBUTTON_HPP_

#include "../listener/ButtonListener.hpp"
#include "../screen/CharacterScreen.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class CharacterScreen_CharacterButton : public ButtonListener {

	public:
		CharacterScreen_CharacterButton(CharacterScreen* view);
		void pressed(void* origin);

	private:
		CharacterScreen* m_view;
	};


}


#endif /* CHARACTERSCREEN_CHARACTERBUTTON_HPP_ */
