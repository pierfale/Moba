/*
 * InnerWindowListener.hpp
 *
 *  Created on: 9 avr. 2013
 *      Author: pierre
 */

#ifndef INNERWINDOWLISTENER_HPP_
#define INNERWINDOWLISTENER_HPP_

namespace graphics {

	class InnerWindowListener {

	public:
		virtual ~InnerWindowListener();
		virtual void pressed(void* origin);
		virtual void released(void* origin);
		virtual void mouseEntered(void* origin);
		virtual void mouseLeft(void* origin);
		virtual void selected(void* origin);
		virtual void unselected(void* origin);
	};

}

#endif /* INNERWINDOWLISTENER_HPP_ */
