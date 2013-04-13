/*
 * Layout.hpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#ifndef LAYOUT_HPP_
#define LAYOUT_HPP_

#include <boost/ptr_container/ptr_vector.hpp>



namespace graphics {

	class Container;

	class Layout {

	public:
		virtual ~Layout();
		virtual void validate() = 0;
		void setContainer(graphics::Container* container);
		virtual std::string getLayoutName();

	protected:
		graphics::Container* m_container;

	};

}

#endif /* LAYOUT_HPP_ */
