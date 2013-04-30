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

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class Container : public Component {

	public:
		Container();
		~Container();
		void add(Component* component);
		void remove(Component* component);
		void replace (Component* old, Component* nw);
		void clear();
		int childSize();
		Component* getChild(int i);
		void setWindow(Window* window);
		void setLayout(Layout* layout);
		void setSelected(bool state, bool force = false);
		void setBackground(std::string path, Repeat repeat);
		void setBackgroundColor(sf::Color color);

		bool isSelectable();
		bool isContainer();

		std::string getComponentName();

		void validate();
		bool event(sf::Event* event, bool used);
		void draw(sf::RenderWindow* render);

		std::string toString(bool recursive = false);

	protected:
		boost::ptr_vector<Component> m_components;
		boost::ptr_vector<Component> m_componentsAbs;
		Layout* m_layout;
		sf::Texture* m_background;
		sf::Color m_backgroundColor;
		Repeat m_repeat;



	};

}


#endif /* CONTAINER_HPP_ */
