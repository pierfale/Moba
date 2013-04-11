/*
 * Container.cpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#include "Container.hpp"
#include "../layout/VerticalLayout.hpp"

namespace graphics {

	Container::Container() : m_background(NULL) {
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
	}

	bool Container::event(sf::Event* event, bool used) {
		for(boost::ptr_vector<Component>::reverse_iterator it = m_components.rbegin(); it != m_components.rend(); ++it) {
			used = it->event(event, used);
		}
		return used;
	}

	void Container::draw(sf::RenderWindow* render) {
		util::Coordinates coord = getRealCoord();
		if(m_background != NULL)
			util::Graphics::repeat(render, m_background, sf::IntRect(coord.x, coord.y, m_width, m_height), m_repeat);
		for(boost::ptr_vector<Component>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			it->draw(render);
		}
	}

}



