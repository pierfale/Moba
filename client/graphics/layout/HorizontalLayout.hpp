/*
 * HorizontalLayout.hpp
 *
 *  Created on: 27 avr. 2013
 *      Author: pierre
 */

#ifndef HORIZONTALLAYOUT_HPP_
#define HORIZONTALLAYOUT_HPP_

#include "Layout.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class HorizontalLayout : public Layout {

	public:
		void validate();
		std::string getLayoutName();

	};

}



#endif /* HORIZONTALLAYOUT_HPP_ */
