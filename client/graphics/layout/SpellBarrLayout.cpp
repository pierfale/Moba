/*
 * SpellBarrLayout.cpp
 *
 *  Created on: 27 avr. 2013
 *      Author: Béni
 */

#include "SpellBarrLayout.h"
#include "../component/Container.hpp"

namespace graphics {

	SpellBarrLayout::~SpellBarrLayout() {}

	void SpellBarrLayout::validate() {
		for (int i = 0 ; i < m_container->childSize() ; ++i) {
			m_container->getChild(i)->setCoord(util::CoordInt(i*SIZE_ICON, 0));
			m_container->getChild(i)->setSize(SIZE_ICON,SIZE_ICON);
		}
	}

	std::string SpellBarrLayout::getLayoutName() {
		return "SpellBarrLayout";
	}

} /* namespace graphics */
