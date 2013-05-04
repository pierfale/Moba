/*
 * CharacterScreen_MainButton.hpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#ifndef CHARACTERSCREEN_MAINBUTTON_HPP_
#define CHARACTERSCREEN_MAINBUTTON_HPP_

#include "../listener/ButtonListener.hpp"
#include "../screen/CharacterScreen.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class CharacterScreen_MainButton : public ButtonListener {


	public:
		CharacterScreen_MainButton(CharacterScreen* view);
		void pressed(void* origin);

	private:
		CharacterScreen* m_view;
	};


}


#endif /* CHARACTERSCREEN_MAINBUTTON_HPP_ */
