/*
 * Layout.cpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#include "Layout.hpp"
#include "../component/Container.hpp"

namespace graphics {

	Layout::~Layout() {

	}

	void Layout::setContainer(Container* container) {
		m_container = container;
	}

	std::string Layout::getLayoutName() {
		return "Layout";
	}

}
