/*
 * VirtualAnimation.cpp
 *
 *  Created on: 20 avr. 2013
 *      Author: B�ni
 */

#include "Animation.hpp"

namespace graphics {

	Animation::Animation() : m_done(false) {

	}

	Animation::~Animation() {

	}

	bool Animation::isDone() {
		return m_done;
	}


} /* namespace graphics */
