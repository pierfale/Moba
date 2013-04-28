/*
 * LineStyle.cpp
 *
 *  Created on: 13 avr. 2013
 *      Author: pierre
 */

#include "LineStyle.hpp"

namespace graphics {

	LineStyle::LineStyle(){
		 m_lineImage = NULL;
	}

	void LineStyle::setLineImage(std::string image) {
		m_lineImage = ImageLoader::get(image);
	}

	sf::Texture* LineStyle::line() {
		return m_lineImage;
	}

}


