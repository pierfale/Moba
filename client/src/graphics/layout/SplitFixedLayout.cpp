/*
 * SplitFixedLayout.cpp
 *
 *  Created on: 10 avr. 2013
 *      Author: pierre
 */

#include "SplitFixedLayout.hpp"
#include "../component/Container.hpp"

namespace graphics {

	SplitFixedLayout::SplitFixedLayout(Direction direction, Fixed fixed, int fixedSize) : m_direction(direction), m_fixed(fixed), m_fixedSize(fixedSize) {

	}

	void SplitFixedLayout::validate() {
		if(m_container->childSize() == 2) {
			if(m_direction == vertical) {
				for(int i=0; i<2; i++) {
					if(i == m_fixed) {
						if(i == 0)
							m_container->getChild(i)->setCoord(util::CoordInt(0,0));
						else
							m_container->getChild(i)->setCoord(util::CoordInt(m_container->getWidth()-m_fixedSize,0));
						m_container->getChild(i)->setSize(m_fixedSize, m_container->getHeight());
					}
					else {
						if(i == 0)
							m_container->getChild(i)->setCoord(util::CoordInt(0,0));
						else
							m_container->getChild(i)->setCoord(util::CoordInt(m_fixedSize,0));
						m_container->getChild(i)->setSize(m_container->getWidth()-m_fixedSize, m_container->getHeight());
					}
				}
			}
			else {
				for(int i=0; i<2; i++) {
					if(i == m_fixed) {
						if(i == 0)
							m_container->getChild(i)->setCoord(util::CoordInt(0,0));
						else
							m_container->getChild(i)->setCoord(util::CoordInt(0,m_container->getHeight()-m_fixedSize));
						m_container->getChild(i)->setSize(m_container->getWidth(), m_fixedSize);
					}
					else {
						if(i == 0)
							m_container->getChild(i)->setCoord(util::CoordInt(0,0));
						else
							m_container->getChild(i)->setCoord(util::CoordInt(0, m_fixedSize));
						m_container->getChild(i)->setSize(m_container->getWidth(), m_container->getHeight()-m_fixedSize);
					}
				}
			}
		}
		else {
			log_err "SplitFixedLayout work only with 2 components  [Container "+util::Cast::ptrToString(m_container)+"]" end_log_err;
		}
	}

	std::string SplitFixedLayout::getLayoutName() {
		return "SplitFixedLayout";
	}
}


