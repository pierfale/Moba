/*
 * SelectTeamScreen_MainButton.hpp
 *
 *  Created on: 27 avr. 2013
 *      Author: pierre
 */

#ifndef SELECTTEAMSCREEN_MAINBUTTON_HPP_
#define SELECTTEAMSCREEN_MAINBUTTON_HPP_

#include "../listener/ButtonListener.hpp"
#include "../screen/SelectTeamScreen.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class SelectTeamScreen_MainButton : public ButtonListener {


	public:
		SelectTeamScreen_MainButton(SelectTeamScreen* view);
		void pressed(void* origin);

	private:
		SelectTeamScreen* m_view;
	};

}


#endif /* SELECTTEAMSCREEN_MAINBUTTON_HPP_ */
