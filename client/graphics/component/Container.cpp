/*
 * Container.cpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#include "Container.hpp"
#include "../layout/VerticalLayout.hpp"

namespace graphics {

	Container::Container() : m_background(NULL), m_backgroundColor(sf::Color::Transparent), m_repeat(full) {
		m_layout = new VerticalLayout();
		m_layout->setContainer(this);
		//log_out "Ref "+util::Cast::ptrToString(this)+": Create "+getComponentName() end_log_out;
	}

	Container::~Container() {
		delete m_layout;
		while(m_components.size() > 0) {
			m_components.pop_back().release();
		}
		while(m_componentsAbs.size() > 0) {
			m_componentsAbs.pop_back().release();
		}
	}

	void  Container::add(Component* component) {
		component->setParent(this);
		component->setWindow(m_window);
		if(component->isAbsolute())
			m_componentsAbs.push_back(component);
		else
			m_components.push_back(component);
		m_layout->validate();
		//log_out "Ref "+util::Cast::ptrToString(this)+": Add "+component->getComponentName()+" (ref "+util::Cast::ptrToString(component)+") in "+getComponentName() end_log_out;
	}

	void Container::remove(Component* component) {
		for(boost::ptr_vector<Component>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			if(&(*it) == component) {
				m_components.release(it).release();
				validate();
				break;
			}
		}
		for(boost::ptr_vector<Component>::iterator it = m_componentsAbs.begin(); it != m_componentsAbs.end(); ++it) {
			if(&(*it) == component) {
				m_componentsAbs.release(it).release();
				validate();
				break;
			}
		}
	}

	void Container::replace(Component* old, Component* nw) {
		for(boost::ptr_vector<Component>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			if(&(*it) == old) {
				m_components.replace(it, nw).release();
				nw->setParent(this);
				nw->setWindow(m_window);
				validate();
				break;
			}
		}
		for(boost::ptr_vector<Component>::iterator it = m_componentsAbs.begin(); it != m_componentsAbs.end(); ++it) {
			if(&(*it) == old) {
				m_componentsAbs.replace(it, nw).release();
				nw->setParent(this);
				nw->setWindow(m_window);
				validate();
				break;
			}
		}
	}

	void Container::clear() {
		while(m_components.size() > 0) {
			m_components.release(m_components.begin()).release();
		}
		while(m_componentsAbs.size() > 0) {
			m_componentsAbs.release(m_componentsAbs.begin()).release();
		}
		validate();
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
		validate();
	}

	void Container::setSelected(bool state, bool force) {
		m_selected = state;
		for(boost::ptr_vector<Component>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			it->setSelected(state, force);
		}
		for(boost::ptr_vector<Component>::iterator it = m_componentsAbs.begin(); it != m_componentsAbs.end(); ++it) {
			it->setSelected(state, force);
		}
	}

	void Container::setWindow(Window* window) {
		m_window = window;
		for(boost::ptr_vector<Component>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			it->setWindow(window);
		}
		for(boost::ptr_vector<Component>::iterator it = m_componentsAbs.begin(); it != m_componentsAbs.end(); ++it) {
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
		Component::validate();
		m_layout->validate();
		for(boost::ptr_vector<Component>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			it->validate();
		}
		for(boost::ptr_vector<Component>::iterator it = m_componentsAbs.begin(); it != m_componentsAbs.end(); ++it) {
			it->validate();
		}
	}

	bool Container::event(sf::Event* event, bool used) {
		for(boost::ptr_vector<Component>::reverse_iterator it = m_componentsAbs.rbegin(); it != m_componentsAbs.rend(); ++it) {
			used = it->event(event, used);
		}
		for(boost::ptr_vector<Component>::reverse_iterator it = m_components.rbegin(); it != m_components.rend(); ++it) {
			used = it->event(event, used);
		}
		return used;
	}

	void Container::draw(sf::RenderWindow* render) {
		util::CoordInt coord = getRealCoord();
		sf::RectangleShape rect(sf::Vector2f(m_width, m_height));
		rect.setPosition(coord.x, coord.y);
		rect.setFillColor(m_backgroundColor);
		render->draw(rect);
		if(m_background != NULL)
			util::Graphics::repeat(render, m_background, sf::IntRect(coord.x, coord.y, m_width, m_height), m_repeat);
		for(boost::ptr_vector<Component>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			it->draw(render);
		}
		for(boost::ptr_vector<Component>::iterator it = m_componentsAbs.begin(); it != m_componentsAbs.end(); ++it) {
			it->draw(render);
		}
	}

	std::string Container::toString(bool recursive) {
		std::string r = "["+util::Cast::ptrToString(this)+":"+getComponentName()+":width="+util::Cast::intToString(m_width)+", height="+util::Cast::intToString(m_height)+
						",x="+util::Cast::intToString(m_coord.x)+",y="+util::Cast::intToString(m_coord.y)+", layout="+m_layout->getLayoutName()+", parent="+util::Cast::ptrToString(m_parent)+"]\n";
		for(boost::ptr_vector<Component>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			r += "   "+it->toString()+"\n";
		}
		for(boost::ptr_vector<Component>::iterator it = m_componentsAbs.begin(); it != m_componentsAbs.end(); ++it) {
			r += "   "+it->toString()+"\n";
		}
		return r;
	}

}



