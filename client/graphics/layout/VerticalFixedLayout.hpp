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

namespace graphics {

	class VerticalFixedLayout : public Layout {

	public:
		enum Length {full, fixed};
		VerticalFixedLayout(Length length);
		void validate();
		std::string getLayoutName();

	private:
		Length m_length;

	};

}

#endif /* VERTICALFIXEDLAYOUT_HPP_ */
