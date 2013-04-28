/*
 * ButtonImage.hpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#ifndef BUTTONIMAGE_HPP_
#define BUTTONIMAGE_HPP_

#include "../component/Button.hpp"
#include "../ImageLoader.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class ButtonImage : public Button {

	public:
		ButtonImage(std::string image, BasicStyle* style=NULL);
		void draw(sf::RenderWindow* render);

	private:
		sf::Texture* m_image;
	};
}



#endif /* BUTTONIMAGE_HPP_ */
