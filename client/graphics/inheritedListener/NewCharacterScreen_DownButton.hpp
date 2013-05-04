/*
 * NewCharacterScreen_DownButton.hpp
 *
 *  Created on: 15 avr. 2013
 *      Author: pierre
 */

#ifndef NEWCHARACTERSCREEN_DOWNBUTTON_HPP_
#define NEWCHARACTERSCREEN_DOWNBUTTON_HPP_

#include "../listener/ButtonListener.hpp"
#include "../screen/NewCharacterScreen.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class NewCharacterScreen_DownButton : public ButtonListener {

	public:
		NewCharacterScreen_DownButton(NewCharacterScreen* view);
		void pressed(void* origin);

	private:
		NewCharacterScreen* m_view;
	};

}

#endif /* NEWCHARACTERSCREEN_DOWNBUTTON_HPP_ */
