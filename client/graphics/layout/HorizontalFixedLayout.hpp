/*
 * HorizontalFixedLayout.hpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#ifndef HORIZONTALFIXEDLAYOUT_HPP_
#define HORIZONTALFIXEDLAYOUT_HPP_

#include "Layout.hpp"
#include "../component/Component.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class HorizontalFixedLayout : public Layout {

	public:
		enum Length {full, fixed};
		HorizontalFixedLayout(Length length, Length vertical);
		void validate();
		std::string getLayoutName();

	private:
		Length m_length;
		Length m_vertical;
	};

}


#endif /* HORIZONTALFIXEDLAYOUT_HPP_ */
