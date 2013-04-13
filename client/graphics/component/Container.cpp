/*
 * Container.cpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#include "Container.hpp"
#include "../layout/VerticalLayout.hpp"

namespace graphics {

	Container::Container() : m_background(NULL), m_backgroundColor(sf::Color::Transparent) {
		m_layout = new VerticalLayout();
		m_layout->setContainer(this);
		client::Log::out("Ref "+util::Cast::ptrToInt(this)+": Create "+getComponentName());
	}

	Container::~Container() {
		delete m_layout;
	}

	void  Container::add(Component* component) {
		component->setParent(this);
		component->setWindow(m_window);
		m_components.push_back(component);
		m_layout->validate();
		client::Log::out("Ref "+util::Cast::ptrToInt(this)+": Add "+component->getComponentName()+" (ref "+util::Cast::ptrToInt(component)+") in "+getComponentName());
	}

	void Container::replace(Component* old, Component* nw) {
		for(boost::ptr_vector<Component>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			if(&(*it) == old) {
				m_components.replace(it, nw);
				nw->setParent(this);
				nw->setWindow(m_window);
				validate();
				break;
			}
		}
	}

	int Container::childSize() {
		return m_components.size();
	}

	Component* Container::getChild(int i) {
		return &m_components.at(i);
	}

	void Container::setLayout(Layout* layout) {
		m_layout = layout;
		m_layout->setContainer(this);
		m_layout->validate();
	}

	void Container::setSelected(bool state) {
		m_selected = state;
		for(boost::ptr_vector<Component>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			it->setSelected(state);
		}
	}

	void Container::setWindow(Window* window) {
		m_window = window;
		for(boost::ptr_vector<Component>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			it->setWindow(window);
		}
	}

	void Container::setBackground(std::string path, Repeat repeat) {
		m_background = ImageLoader::get(path);
		m_repeat = repeat;
	}

	void Container::setBackgroundColor(sf::Color color) {
		m_backgroundColor = color;
	}

	bool Container::isSelectable() {
		return false;
	}

	bool Container::isContainer() {
		return true;
	}

	std::string Container::getComponentName() {
		return "Container";
	}

	void Container::validate() {
		m_layout->validate();
		for(boost::ptr_vector<Component>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			it->validate();
		}
	}

	bool Container::event(sf::Event* event, bool used) {
		for(boost::ptr_vector<Component>::reverse_iterator it = m_components.rbegin(); it != m_components.rend(); ++it) {
			used = it->event(event, used);
		}
		return used;
	}

	void Container::draw(sf::RenderWindow* render) {
		util::Coordinates coord = getRealCoord();
		sf::RectangleShape rect(sf::Vector2f(m_width, m_height));
		rect.setPosition(coord.x, coord.y);
		rect.setFillColor(m_backgroundColor);
		render->draw(rect);
		if(m_background != NULL)
			util::Graphics::repeat(render, m_background, sf::IntRect(coord.x, coord.y, m_width, m_height), m_repeat);
		for(boost::ptr_vector<Component>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			it->draw(render);
		}
	}

	std::string Container::toString(bool recursive) {
		std::string r = "["+util::Cast::ptrToInt(this)+":"+getComponentName()+":width="+util::Cast::intToString(m_width)+", height="+util::Cast::intToString(m_height)+
						",x="+util::Cast::intToString(m_coord.x)+",y="+util::Cast::intToString(m_coord.y)+", layout="+m_layout->getLayoutName()+", parent="+util::Cast::ptrToInt(m_parent)+"]\n";
		for(boost::ptr_vector<Component>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			r += "   "+it->toString()+"\n";
		}
		return r;
	}

}



