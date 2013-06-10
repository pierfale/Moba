/*
 * ScrollBar.cpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#include "ScrollBar.hpp"

namespace graphics {

	ScrollBar::ScrollBar(ScrollBarStyle* style) : m_style(style), m_pane(NULL),  m_offsetX(0), m_offsetY(0) {
		isHeightMove = false;
		m_offsetInitY = 0;
	}

	void ScrollBar::setContentPane(Component* pane) {
		m_pane = pane;
		m_pane->setParent(this);
		m_pane->setWindow(m_window);
	}

	util::CoordInt ScrollBar::getRealCoord() {
		if(m_parent == NULL)
			return m_coord;
		return util::CoordInt(m_coord.x+m_parent->getRealCoord().x-m_offsetX, m_coord.y+m_parent->getRealCoord().y-m_offsetY);
	}

	void ScrollBar::setScrollDown() {
		m_offsetY = m_pane->getHeight()-m_height;
	}

	bool ScrollBar::event(sf::Event* event, bool used) {
		if(m_pane == NULL)
			return used;
		util::CoordInt coord = Component::getRealCoord();
		if(event->type == sf::Event::MouseButtonPressed) {
			if(m_pane->getHeight() > m_height) {
				int size = ((float)m_height/(float)m_pane->getHeight())*(float)m_height;
				int offset = ((float)m_height/(float)m_pane->getHeight())*(float)m_offsetY;
				if(event->mouseButton.x >= coord.x+m_width-m_style->barCenter()->getGlobalBounds().width && event->mouseButton.x < coord.x+m_width &&
					event->mouseButton.y >= coord.y+offset && coord.y+offset+size) {
					m_mouseInit = util::CoordInt(event->mouseButton.x, event->mouseButton.y);
					m_offsetInitY = m_offsetY;
					isHeightMove = true;
				}
			}
		}
		else if(event->type == sf::Event::MouseButtonReleased) {
			isHeightMove = false;
		}
		else if(event->type == sf::Event::MouseLeft) {
			isHeightMove = false;
		}
		else if(event->type == sf::Event::MouseMoved) {
			if(isHeightMove) {
				m_offsetY = m_offsetInitY+event->mouseMove.y-m_mouseInit.y;
				int offset = ((float)m_height/(float)m_pane->getHeight())*(float)m_offsetY;
				int size = ((float)m_height/(float)m_pane->getHeight())*(float)m_height;

				if(m_offsetY < 0)
					m_offsetY = 0;
				if(offset+size >= m_height)
					m_offsetY = m_pane->getHeight()-m_height;

			}
		}
		return used;
	}

	void ScrollBar::draw(sf::RenderWindow* render) {
		if(m_pane == NULL || m_style == NULL)
			return;
		util::CoordInt coord =  Component::getRealCoord();
		sf::View tmp = render->getView();
		sf::View view;
		view.reset(sf::FloatRect(coord.x, coord.y, m_width,  m_height));
		view.setViewport(sf::FloatRect((float)coord.x/(float)render->getSize().x, (float)coord.y/(float)render->getSize().y, (float)m_width/(float)render->getSize().x, (float)m_height/(float)render->getSize().y));
		render->setView(view);

		m_pane->draw(render);

		if(m_pane->getWidth() > m_width) {

		}

		if(m_pane->getHeight() > m_height) {
			int offset = ((float)m_height/(float)m_pane->getHeight())*(float)m_offsetY;
			int size = ((float)m_height/(float)m_pane->getHeight())*(float)m_height;
			m_style->backgroundTop()->setPosition(coord.x+m_width-m_style->backgroundCenter()->getGlobalBounds().width, coord.y);
			render->draw(*m_style->backgroundTop());

			m_style->backgroundCenter()->setPosition(coord.x+m_width-m_style->backgroundCenter()->getGlobalBounds().width, coord.y+m_style->backgroundTop()->getGlobalBounds().height);
			m_style->backgroundCenter()->setScale(1.0, m_height-2*m_style->backgroundTop()->getGlobalBounds().height);
			render->draw(*m_style->backgroundCenter());

			m_style->backgroundBot()->setPosition(coord.x+m_width-m_style->backgroundCenter()->getGlobalBounds().width, coord.y+m_height-m_style->backgroundBot()->getGlobalBounds().height);
			render->draw(*m_style->backgroundBot());

			m_style->barTop()->setPosition(coord.x+m_width-m_style->barCenter()->getGlobalBounds().width, coord.y+offset);
			render->draw(*m_style->barTop());

			m_style->barCenter()->setPosition(coord.x+m_width-m_style->barCenter()->getGlobalBounds().width, coord.y+m_style->barTop()->getGlobalBounds().height+offset);
			m_style->barCenter()->setScale(1.0, size-2*m_style->barTop()->getGlobalBounds().height);
			render->draw(*m_style->barCenter());

			m_style->barBot()->setPosition(coord.x+m_width-m_style->barCenter()->getGlobalBounds().width, coord.y+offset+size-m_style->barTop()->getGlobalBounds().height);
			render->draw(*m_style->barBot());
		}


		render->setView(tmp);
	}
}


