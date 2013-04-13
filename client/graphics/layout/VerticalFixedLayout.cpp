/*
 * VerticalFixedLayout.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#include "VerticalFixedLayout.hpp"
#include "../component/Container.hpp"

namespace graphics {

	VerticalFixedLayout::VerticalFixedLayout(Length length) : m_length(length) {

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
				m_container->getChild(i)->setCoord(util::Coordinates(0, y));
				m_container->getChild(i)->setSize(m_container->getWidth(), m_container->getChild(i)->getHeight());
				y += m_container->getChild(i)->getHeight()+((m_container->getHeight()-total)/m_container->childSize())/2;
			}
		}
		else {
			int y = 0;
			for(int i=0; i<m_container->childSize(); i++) {
				m_container->getChild(i)->setCoord(util::Coordinates(0, y));
				m_container->getChild(i)->setSize(m_container->getWidth(), m_container->getChild(i)->getHeight());
				y += m_container->getChild(i)->getHeight();
			}
		}
	}

	std::string VerticalFixedLayout::getLayoutName() {
		return "VerticalFixedLayout";
	}

}

