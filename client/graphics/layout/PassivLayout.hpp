/*
 * PassivLayout.hpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#ifndef PASSIVLAYOUT_HPP_
#define PASSIVLAYOUT_HPP_

#include "Layout.hpp"
#include "../component/Component.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class PassivLayout : public Layout {

	public:
		void validate();
		std::string getLayoutName();

	};

}


#endif /* PASSIVLAYOUT_HPP_ */
