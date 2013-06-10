/*
 * HorizontalLayout.cpp
 *
 *  Created on: 27 avr. 2013
 *      Author: pierre
 */

#include "HorizontalLayout.hpp"
#include "../component/Container.hpp"

namespace graphics {

	void HorizontalLayout::validate() {
		for(int i=0; i<m_container->childSize(); i++) {
			m_container->getChild(i)->setCoord(util::CoordInt(i*(m_container->getWidth()/m_container->childSize()), 0));
			m_container->getChild(i)->setSize(m_container->getWidth()/m_container->childSize(), m_container->getHeight());
		}
	}

	std::string HorizontalLayout::getLayoutName() {
		return "HorizontalLayout";
	}

}



