/*
 * Line.cpp
 *
 *  Created on: 13 avr. 2013
 *      Author: pierre
 */

#include "Line.hpp"

namespace graphics {

	Line::Line(util::Coordinates origin, util::Coordinates target, LineStyle* style) : m_style(style) {
		m_origin = origin;
		m_target = target;
		m_width = origin.x > target.x ? origin.x - target.x : target.x - origin.x;
		m_height = origin.y > target.y ? origin.y - target.y : target.y - origin.y;
	}

	bool Line::event(sf::Event* event, bool used) {
		return used;
	}

	void Line::draw(sf::RenderWindow* render) {
		if(m_style == NULL) {
			log_err "No style has been applied to the component "+getComponentName() end_log_err;
			return;
		}

		util::Coordinates coord = getRealCoord();

		sf::Sprite verticalUp, horizontal, verticalDown;

		int width = m_origin.x > m_target.x ? m_origin.x - m_target.x : m_target.x - m_origin.x;
		int height = m_origin.y > m_target.y ? m_origin.y - m_target.y : m_target.y - m_origin.y;

		int x =  m_origin.x < m_target.x ? m_origin.x : m_target.x;
		int y = m_origin.y < m_target.y ? m_origin.y : m_target.y;

		if(height > 0) {
			verticalUp.setTexture(*m_style->line());
			verticalUp.setPosition(coord.x+m_origin.x-m_style->line()->getSize().x/2,coord.y+y);
			verticalUp.setScale(1.0, (height/2)/m_style->line()->getSize().y);
			render->draw(verticalUp);
		}

		if(width > 0) {
			horizontal.setTexture(*m_style->line());
			horizontal.setPosition(coord.x+x-m_style->line()->getSize().x/2, coord.y+y+(height/2)-m_style->line()->getSize().y/2);
			horizontal.setScale((width+m_style->line()->getSize().x)/m_style->line()->getSize().x, 1.0);
			render->draw(horizontal);
		}

		if(height > 0) {
			verticalUp.setTexture(*m_style->line());
			verticalUp.setPosition(coord.x+m_target.x-m_style->line()->getSize().x/2,coord.y+y+(height/2));
			verticalUp.setScale(1.0, (height/2)/m_style->line()->getSize().y);
			render->draw(verticalUp);
		}

	}

}


