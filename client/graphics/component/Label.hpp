/*
 * Label.hpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#ifndef LABEL_HPP_
#define LABEL_HPP_

#include <string>
#include <boost/ptr_container/ptr_vector.hpp>

#include "../../util/Util.hpp"
#include "Component.hpp"
#include "../style/BasicStyle.hpp"
#include "../listener/LabelListener.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class Label : public Component {

	public:
		enum Align {alignLeft, alignCenter, alignRight};
		Label(std::string text, BasicStyle* style=NULL);
		~Label();
		void draw(sf::RenderWindow* render);
		void addListener(LabelListener* listener);
		bool event(sf::Event* event, bool used);
		void setStyle(BasicStyle* style);
		void setAlign(Align align);
		void setMinimalSize();
		void setText(std::string);

		std::string getText();
		std::string getComponentName();

		bool isSelectable();

	private:
		std::string m_text;
		BasicStyle* m_style;
		boost::ptr_vector<LabelListener> m_listener;
		Align m_align;

	};

}


#endif /* LABEL_HPP_ */
