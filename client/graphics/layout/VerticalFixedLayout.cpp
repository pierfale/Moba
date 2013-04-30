/*
 * VerticalFixedLayout.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#include "VerticalFixedLayout.hpp"
#include "../component/Container.hpp"

namespace graphics {

	VerticalFixedLayout::VerticalFixedLayout(Length length, Length horizontal) : m_length(length), m_horizontal(horizontal) {

	}

	void VerticalFixedLayout::validate() {
		if(m_length == full) {
			int total = 0;
			for(int i=0; i<m_container->childSize(); i++) {
				total += m_container->getChild(i)->getHeight();
			}
			int y = 0;
			for(int i=0; i<m_container->childSize(); i++) {
				y += ((m_container->getHeight()-total)/m_container->childSize())/2;
				if(m_horizontal == full) {
					m_container->getChild(i)->setCoord(util::CoordInt(0, y));
					m_container->getChild(i)->setSize(m_container->getWidth(), m_container->getChild(i)->getHeight());
				}
				else
					m_container->getChild(i)->setCoord(util::CoordInt((m_container->getWidth()-m_container->getChild(i)->getWidth())/2, y));
				y += m_container->getChild(i)->getHeight()+((m_container->getHeight()-total)/m_container->childSize())/2;
			}
		}
		else {
			int y = 0;
			for(int i=0; i<m_container->childSize(); i++) {
				if(m_horizontal == full) {
					m_container->getChild(i)->setCoord(util::CoordInt(0, y));
					m_container->getChild(i)->setSize(m_container->getWidth(), m_container->getChild(i)->getHeight());
				}
				else
					m_container->getChild(i)->setCoord(util::CoordInt((m_container->getWidth()-m_container->getChild(i)->getWidth())/2, y));
				y += m_container->getChild(i)->getHeight();
			}
		}
	}

	std::string VerticalFixedLayout::getLayoutName() {
		return "VerticalFixedLayout";
	}

}

