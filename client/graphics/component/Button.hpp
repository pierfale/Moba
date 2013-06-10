/*
 * Button.hpp
 *
 *  Created on: 7 avr. 2013
 *      Author: pierre
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <boost/ptr_container/ptr_vector.hpp>

#include "../../util/Util.hpp"
#include "Component.hpp"
#include "../style/BasicStyle.hpp"
#include "../listener/ButtonListener.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class Button : public Component {
	public:
		Button(std::string text, BasicStyle* style=NULL);
		~Button();
		void draw(sf::RenderWindow* render);
		void addListener(ButtonListener* listener);
		bool event(sf::Event* event, bool used);
		void setSelected(bool state, bool force = false);
		void setStyle(BasicStyle* style);
		void setMinimalSize();
		void setText(std::string);

		std::string getComponentName();

		std::string getText();

	protected:
		std::string m_text;
		BasicStyle* m_style;
		boost::ptr_vector<ButtonListener> m_listener;
	};
}
#endif


