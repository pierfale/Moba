/*
 * BufferDraw.cpp
 *
 *  Created on: 9 mai 2013
 *      Author: pierre
 */

#include "BufferDraw.hpp"

namespace  graphics {

	BufferDraw::BufferDraw() {

	}

	void BufferDraw::clear() {
		while(m_drawable.size() > 0) {
			m_drawable.release(m_drawable.begin()).release();
		}
	}

	void BufferDraw::add(BufferDrawable* drawable) {
		unsigned int i=0;
		while(i < m_drawable.size() && m_drawable.at(i).getValueY() < drawable->getValueY()) {
			i++;
		}
		m_drawable.insert(m_drawable.begin()+i, drawable);
	}

	void BufferDraw::draw(sf::RenderWindow* render, Camera* cam) {
		for(boost::ptr_vector<BufferDrawable>::iterator it = m_drawable.begin(); it != m_drawable.end(); ++it) {
			it->draw(render, cam);
		}
	}

}


