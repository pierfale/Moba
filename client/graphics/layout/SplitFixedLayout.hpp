/*
 * SplitFixedLayout.hpp
 *
 *  Created on: 10 avr. 2013
 *      Author: pierre
 */

#ifndef SPLITFIXEDLAYOUT_HPP_
#define SPLITFIXEDLAYOUT_HPP_

#include "Layout.hpp"
#include "../component/Component.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class SplitFixedLayout : public Layout {

	public:
		enum Direction {horizontal, vertical};
		enum Fixed {first, second};
		SplitFixedLayout(Direction direction, Fixed fixed, int fixedSize);
		void validate();
		std::string getLayoutName();

	private:

		Direction m_direction;
		Fixed m_fixed;
		int m_fixedSize;

	};

}


#endif /* SPLITFIXEDLAYOUT_HPP_ */
