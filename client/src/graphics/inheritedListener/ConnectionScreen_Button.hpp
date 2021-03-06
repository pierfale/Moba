/*
 * ConnectionScreen_Button.hpp
 *
 *  Created on: 9 avr. 2013
 *      Author: pierre
 */

#ifndef CONNECTIONSCREEN_BUTTON_HPP_
#define CONNECTIONSCREEN_BUTTON_HPP_

#include "../listener/ButtonListener.hpp"
#include "../screen/ConnectionScreen.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class ConnectionScreen_Button : public ButtonListener {


	public:
		ConnectionScreen_Button(ConnectionScreen* view);
		void enter(void* origin);
		void pressed(void* origin);

	private:
		ConnectionScreen* m_view;
	};


}

#endif /* CONNECTIONSCREEN_BUTTON_HPP_ */
