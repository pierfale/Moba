/*
 * BufferDrawable.hpp
 *
 *  Created on: 9 mai 2013
 *      Author: pierre
 */

#ifndef BUFFERDRAWABLE_HPP_
#define BUFFERDRAWABLE_HPP_

#include <SFML/Graphics.hpp>
#include "Camera.h"

namespace graphics {

	class BufferDrawable {

	public:
		virtual ~BufferDrawable() {

		}
		virtual int getValueY() = 0;
		virtual void draw(sf::RenderWindow* render, Camera* cam) = 0;

	};
}


#endif /* BUFFERDRAWABLE_HPP_ */
