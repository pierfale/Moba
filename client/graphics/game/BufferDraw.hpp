/*
 * BufferDraw.hpp
 *
 *  Created on: 9 mai 2013
 *      Author: pierre
 */

#ifndef BUFFERDRAW_HPP_
#define BUFFERDRAW_HPP_

#include <SFML/Graphics.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "BufferDrawable.hpp"

namespace graphics {

	class BufferDraw {

	public:
		BufferDraw();
		void clear();
		void add(BufferDrawable* drawable);
		void draw(sf::RenderWindow* render, Camera* cam);

	private:
		boost::ptr_vector<BufferDrawable> m_drawable;

	};

}

#endif /* BUFFERDRAW_HPP_ */
