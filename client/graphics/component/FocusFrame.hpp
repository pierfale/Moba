/*
 * FocusFrame.hpp
 *
 *  Created on: 24 mai 2013
 *      Author: pierre
 */

#ifndef FOCUSFRAME_HPP_
#define FOCUSFRAME_HPP_

#include "Component.hpp"
#include "String.hpp"
#include "../style/BasicStyle.hpp"

namespace graphics {

	class FocusFrame : public Component {

	public:
		FocusFrame(std::string title, std::string contents, BasicStyle* style=NULL);
		~FocusFrame();
		void draw(sf::RenderWindow* render);
		bool event(sf::Event* event, bool used);

	private:
		String m_text;
		BasicStyle* m_style;
	};

}


#endif /* FOCUSFRAME_HPP_ */
