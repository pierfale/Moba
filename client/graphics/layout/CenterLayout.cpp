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
			m_container->getChild(0)->setCoord(util::Coordinates((m_container->getWidth()-m_container->getChild(0)->getWidth())/2, (m_container->getHeight()-m_container->getChild(0)->getHeight())/2));
		}
		else {
			client::Log::err("Center layout can't work with multiple components [Container "+util::Cast::ptrToInt(m_container)+"]");
		}
	}

}



