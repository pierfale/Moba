/*
 * LabelListener.hpp
 *
 *  Created on: 7 avr. 2013
 *      Author: pierre
 */

#ifndef LABELLISTENER_HPP_
#define LABELLISTENER_HPP_

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class LabelListener {

	public:
		virtual ~LabelListener();
		virtual void mouseEntered(void* origin);
		virtual void mouseLeft(void* origin);
	};

}

#endif /* BUTTONLISTENER_HPP_ */
