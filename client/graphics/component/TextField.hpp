/*
 * TextField.hpp
 *
 *  Created on: 7 avr. 2013
 *      Author: pierre
 */

#ifndef TEXTFIELD_HPP_
#define TEXTFIELD_HPP_

#define FRAME_TIME 0.7

#include "Component.hpp"
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/timer.hpp>
#include "../style/BasicStyle.hpp"
#include "../listener/TextFieldListener.hpp"

namespace graphics {

	class TextField : public Component {
	public:
		TextField(BasicStyle* style=NULL);
		TextField(std::string text, BasicStyle* style=NULL);

		void addListener(TextFieldListener* listener);
		void setSelected(bool state);

		void setMinimalSize();
		void setText(std::string);

		std::string getText();
		std::string getComponentName();

		bool event(sf::Event* event, bool used);
		void draw(sf::RenderWindow* render);

	private:
		std::string m_text;
		boost::ptr_vector<TextFieldListener> m_listener;
		boost::timer m_frame;
		BasicStyle* m_style;
	};

}

#endif /* TEXTFIELD_HPP_ */
