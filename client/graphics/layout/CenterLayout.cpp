/*
 * CenterLayout.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#include "centerLayout.hpp"
#include "../component/Container.hpp"

namespace graphics {

	void CenterLayout::validate() {
		if(m_container->childSize() == 1) {
			m_container->getChild(0)->setCoord(util::CoordInt((m_container->getWidth()-m_container->getChild(0)->getWidth())/2, (m_container->getHeight()-m_container->getChild(0)->getHeight())/2));
		}
		else {
			log_err "Center layout can't work with multiple components [Container "+util::Cast::ptrToString(m_container)+"]" end_log_err;
		}
	}

	std::string CenterLayout::getLayoutName() {
		return "CenterLayout";
	}

}



