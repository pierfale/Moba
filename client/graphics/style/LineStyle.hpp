/*
 * LineStyle.hpp
 *
 *  Created on: 13 avr. 2013
 *      Author: pierre
 */

#ifndef LINESTYLE_HPP_
#define LINESTYLE_HPP_

#include <string>
#include <SFML/Graphics.hpp>

#include "../ImageLoader.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class LineStyle {

	public:
		LineStyle();
		void setLineImage(std::string image);

		sf::Texture* line();

	private:
		sf::Texture* m_lineImage;
	};
}


#endif /* LINESTYLE_HPP_ */
