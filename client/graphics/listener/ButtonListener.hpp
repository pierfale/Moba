/*
 * ButtonListener.hpp
 *
 *  Created on: 7 avr. 2013
 *      Author: pierre
 */

#ifndef BUTTONLISTENER_HPP_
#define BUTTONLISTENER_HPP_

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class ButtonListener {

	public:
		virtual ~ButtonListener();
		virtual void pressed(void* origin);
		virtual void released(void* origin);
		virtual void mouseEntered(void* origin);
		virtual void mouseLeft(void* origin);
		virtual void selected(void* origin);
		virtual void unselected(void* origin);
		virtual void enter(void* origin);
	};

}

#endif /* BUTTONLISTENER_HPP_ */
