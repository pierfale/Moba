/*
 * Graphics.hpp
 *
 *  Created on: 10 avr. 2013
 *      Author: pierre
 */

#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../graphics/Define.hpp"

namespace util {

	class Graphics {

	public:
		static void repeat(sf::RenderWindow* render, sf::Texture* texture, sf::IntRect rect, graphics::Repeat repeat);
	};
}


#endif /* GRAPHICS_HPP_ */
