/*
 * GameListScreen_MainButton.hpp
 *
 *  Created on: 16 avr. 2013
 *      Author: pierre
 */

#ifndef GAMELISTSCREEN_MAINBUTTON_HPP_
#define GAMELISTSCREEN_MAINBUTTON_HPP_

#include "../listener/ButtonListener.hpp"
#include "../screen/GameListScreen.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class GameListScreen_MainButton : public ButtonListener {


	public:
		GameListScreen_MainButton(GameListScreen* view);
		void pressed(void* origin);

	private:
		GameListScreen* m_view;
	};

}

#endif /* GAMELISTSCREEN_MAINBUTTON_HPP_ */
