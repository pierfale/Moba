/*
 * VerticalLayout.cpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#include "VerticalLayout.hpp"
#include "../component/Container.hpp"

namespace graphics {

	void VerticalLayout::validate() {
		for(int i=0; i<m_container->childSize(); i++) {
			m_container->getChild(i)->setCoord(util::CoordInt(0, i*(m_container->getHeight()/m_container->childSize())));
			m_container->getChild(i)->setSize(m_container->getWidth(), m_container->getHeight()/m_container->childSize());
		}
	}

	std::string VerticalLayout::getLayoutName() {
		return "VerticalLayout";
	}

}
