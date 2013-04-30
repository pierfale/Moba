/*
 * Row.cpp
 *
 *  Created on: 16 avr. 2013
 *      Author: pierre
 */

#include "Row.hpp"
#include "Table.hpp"

namespace graphics {

	Row::Row(Table* table) : m_table(table), m_window(NULL), m_width(0), m_height(0) {
		for(int i=0; i<table->columnCount();i++) {
			Label* lbl = new Label("");
			lbl->setParent(table);
			m_components.push_back(lbl);
		}
		m_focus = false;
		m_selected = false;
	}

	Row::~Row() {

	}

	void Row::setSize(int width, int height) {
		m_width = width;
		m_height = height;
	}

	void Row::setSelect(bool state) {
		m_selected = state;
		if(state) {
			for(boost::ptr_vector<TableListener>::iterator it = m_table->getListeners()->begin(); it != m_table->getListeners()->end(); ++it) {
				m_window->addCallFunction(boost::bind(&TableListener::rowSelected, &(*it), this));
			}
		}
	}

	void Row::setCoord(util::CoordInt coord) {
		m_coord = coord;
	}

	void Row::setWindow(Window* window) {
		m_window = window;
	}

	bool Row::set(int i, Component* componant) {
		if(i >= 0 && (unsigned int)i < m_components.size()) {
			m_components.replace(i, componant);
			componant->setParent(m_table);
			return true;
		}
		return false;
	}

	Component* Row::get(int i) {
		if(i >= 0 && (unsigned int)i < m_components.size())
			return &m_components.at(i);
		std::cout << i << " not betwwenn row" << std::endl;
		return NULL;
	}

	bool Row::isFocus() {
		return m_focus;
	}

	bool Row::isSelected() {
		return m_selected;
	}


	void Row::validate() {

	}

	bool Row::event(sf::Event* event, bool used) {
		util::CoordInt coord(m_coord.x+m_table->getRealCoord().x, m_coord.y+m_table->getRealCoord().y);
		if(event->type == sf::Event::MouseButtonPressed) {
			if(!used && event->mouseButton.x > coord.x && event->mouseButton.x < coord.x+m_width
				&& event->mouseButton.y > coord.y && event->mouseButton.y < coord.y+m_height) {
				m_selected = true;
				used = true;
				m_table->setSelect(this);
			}
		}
		else if(event->type == sf::Event::MouseMoved) {
			if(!used && event->mouseMove.x > coord.x && event->mouseMove.x < coord.x+m_width
				&& event->mouseMove.y > coord.y && event->mouseMove.y < coord.y+m_height) {
				m_focus = true;
				used = true;
			}
			else {
				m_focus = false;
			}
		}
		else if(event->type == sf::Event::MouseLeft) {
			m_focus = false;
		}
		return used;
	}

	void Row::draw(sf::RenderWindow render) {

	}
}


