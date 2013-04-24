/*
 * Component.cpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#include "Component.hpp"

namespace graphics {

	Component::Component() : m_width(0), m_height(0), m_parent(NULL), m_window(NULL) {
		m_focus = false;
		m_pressed = false;
		m_selected = false;
		m_visible = true;
		m_enable = true;
	}

	Component::Component(util::Coordinates coord, int width, int height) : m_coord(coord), m_width(width), m_height(height), m_parent(NULL), m_window(NULL) {
		m_focus = false;
		m_pressed = false;
		m_selected = false;
		m_visible = true;
		m_enable = true;
	}

	Component::~Component() {

	}

	void Component::setParent(Component* parent) {
		m_parent = parent;
	}

	void Component::setWindow(Window* window) {
		m_window = window;
	}

	void Component::setCoord(util::Coordinates coord) {
		m_coord = coord;
	}
	void Component::setSize(int width, int height) {
		m_width = width;
		m_height = height;
	}

	void Component::setMinimalSize() {

	}

	void Component::setSelected(bool state, bool force) {
		if(force)
			m_selected = state;
		else
			m_window->setSelectedComponent(this);
	}

	void Component::setVisible(bool state) {
		m_visible = state;
	}

	void Component::setEnable(bool state) {
		m_enable = state;
		if(!m_enable) {
			if(m_selected)
				m_window->setSelectedComponent(NULL);
			m_focus = false;
			m_pressed = false;
		}
	}

	void Component::setWidthCenter() {
		if(m_parent != NULL)
			m_coord.x = (m_parent->getWidth()-m_width)/2;
	}
	void Component::setHeightCenter() {
		if(m_parent != NULL)
			m_coord.y = (m_parent->getHeight()-m_height)/2;
	}

	util::Coordinates Component::getCoord() {
		return m_coord;
	}

	util::Coordinates Component::getRealCoord() {
		if(m_parent == NULL)
			return m_coord;
		return util::Coordinates(m_coord.x+m_parent->getRealCoord().x, m_coord.y+m_parent->getRealCoord().y);
	}

	int Component::getHeight() {
		return m_height;
	}

	int Component::getWidth() {
		return m_width;
	}

	Window* Component::getWindow() {
		if(m_window == NULL)
			log_err "Window is NULL in "+getComponentName()+" (ref "+util::Cast::ptrToString(this)+")" end_log_err;
		return m_window;
	}

	Component* Component::getParent() {
		if(m_parent == NULL)
			log_err "Parent is NULL in "+getComponentName()+" (ref "+util::Cast::ptrToString(this)+")" end_log_err;
		return m_parent;
	}

	std::string Component::getComponentName() {
		return "Component";
	}

	bool Component::isSelectable() {
		return true;
	}

	bool Component::isContainer() {
		return false;
	}

	bool Component::isSelected() {
		return m_selected;
	}

	void Component::validate() {

	}

	std::string Component::toString(bool recursive) {
		return "["+util::Cast::ptrToString(this)+":"+getComponentName()+":width="+util::Cast::intToString(m_width)+", height="+util::Cast::intToString(m_height)+
				",x="+util::Cast::intToString(m_coord.x)+",y="+util::Cast::intToString(m_coord.y)+", parent="+util::Cast::ptrToString(m_parent)+"]";
	}
}


