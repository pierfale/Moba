/*
 * VerticalFixedLayout.hpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#ifndef VERTICALFIXEDLAYOUT_HPP_
#define VERTICALFIXEDLAYOUT_HPP_


#include "Layout.hpp"
#include "../component/Component.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class VerticalFixedLayout : public Layout {

	public:
		enum Length {full, fixed};
		VerticalFixedLayout(Length length, Length horizontal);
		void validate();
		std::string getLayoutName();

	private:
		Length m_length;
		Length m_horizontal;

	};

}

#endif /* VERTICALFIXEDLAYOUT_HPP_ */
