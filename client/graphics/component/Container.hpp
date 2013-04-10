/*
 * Container.hpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include <boost/ptr_container/ptr_vector.hpp>
#include "Component.hpp"
#include "../layout/Layout.hpp"
#include "../Define.hpp"

namespace graphics {

	class Container : public Component {

	public:
		Container();
		~Container();
		void add(Component* component);
		int childSize();
		Component* getChild(int i);
		void setWindow(Window* window);
		void setLayout(Layout* layout);
		void setSelected(bool state);
		void setBackground(std::string path, Repeat repeat);

		bool isSelectable();
		bool isContainer();

		std::string getComponentName();

		void validate();
		bool event(sf::Event* event, bool used);
		void draw(sf::RenderWindow* render);

	protected:
		boost::ptr_vector<Component> m_components;
		Layout* m_layout;
		sf::Texture* m_background;
		Repeat m_repeat;



	};

}


#endif /* CONTAINER_HPP_ */
