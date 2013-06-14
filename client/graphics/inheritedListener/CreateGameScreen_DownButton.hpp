/*
 * CreateGameScreen_DownButton.hpp
 *
 *  Created on: 23 avr. 2013
 *      Author: pierre
 */

#ifndef CREATEGAMESCREEN_DOWNBUTTON_HPP_
#define CREATEGAMESCREEN_DOWNBUTTON_HPP_

#include "../listener/ButtonListener.hpp"
#include "../screen/CreateGameScreen.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class CreateGameScreen_DownButton : public ButtonListener {

	public:
		CreateGameScreen_DownButton(CreateGameScreen* view);
		void pressed(void* origin);

	private:
		CreateGameScreen* m_view;
	};

}



#endif /* CREATEGAMESCREEN_DOWNBUTTON_HPP_ */
