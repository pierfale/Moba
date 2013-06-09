/*
 * HorizontalFixedLayout.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#include "HorizontalFixedLayout.hpp"
#include "../component/Container.hpp"

namespace graphics {

	HorizontalFixedLayout::HorizontalFixedLayout(Length length, Length vertical) : m_length(length), m_vertical(vertical) {

	}

	void HorizontalFixedLayout::validate() {
		if(m_length == full) {
			int total = 0;
			for(int i=0; i<m_container->childSize(); i++) {
				total += m_container->getChild(i)->getWidth();
			}
			int x = 0;
			for(int i=0; i<m_container->childSize(); i++) {
				x += ((m_container->getWidth()-total)/m_container->childSize())/2;
				if(m_vertical == full) {
					m_container->getChild(i)->setSize(m_container->getChild(i)->getWidth(), m_container->getHeight());
					m_container->getChild(i)->setCoord(util::CoordInt(x, 0));
				}
				else
					m_container->getChild(i)->setCoord(util::CoordInt(x, (m_container->getHeight()-m_container->getChild(i)->getHeight())/2));

				x += m_container->getChild(i)->getWidth()+((m_container->getWidth()-total)/m_container->childSize())/2;
			}
		}
		else {
			int x = 0;
			for(int i=0; i<m_container->childSize(); i++) {
				m_container->getChild(i)->setCoord(util::CoordInt(x, 0));
				if(m_vertical == full) {
					m_container->getChild(i)->setSize(m_container->getChild(i)->getWidth(), m_container->getHeight());
					m_container->getChild(i)->setCoord(util::CoordInt(x, 0));
				}
				else
					m_container->getChild(i)->setCoord(util::CoordInt(x, (m_container->getHeight()-m_container->getChild(i)->getHeight())/2));
				x += m_container->getChild(i)->getWidth();
			}
		}
	}

	std::string HorizontalFixedLayout::getLayoutName() {
		return "HorizontalFixed";
	}

}



