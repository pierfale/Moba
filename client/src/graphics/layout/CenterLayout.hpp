/*
 * CenterLayout.hpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#ifndef CENTERLAYOUT_HPP_
#define CENTERLAYOUT_HPP_

#include "Layout.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class CenterLayout : public Layout {

	public:
		void validate();
		std::string getLayoutName();

	};

}


#endif /* CENTERLAYOUT_HPP_ */
