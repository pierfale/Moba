/*
 * FocusFrame.cpp
 *
 *  Created on: 24 mai 2013
 *      Author: pierre
 */

#include "FocusFrame.hpp"

namespace graphics {

	FocusFrame::FocusFrame(std::string title, std::string contents, BasicStyle* style) : m_text("<color=255,255,255><b>"+title+"</b><br/><br/>"+contents+"</color>"), m_style(style) {
		m_text.setParent(this);
		if(style != NULL) {
			m_width = m_text.getWidth()+style->topleft(BasicStyle::normal)->getGlobalBounds().width*2;
			m_height = m_text.getHeight()+style->topleft(BasicStyle::normal)->getGlobalBounds().height*2;
			m_text.setCoord(util::CoordInt(style->topleft(BasicStyle::normal)->getGlobalBounds().width, style->topleft(BasicStyle::normal)->getGlobalBounds().height));
		}
	}

	FocusFrame::~FocusFrame() {

	}

	void FocusFrame::draw(sf::RenderWindow* render) {
		if(m_style == NULL) {
			log_err "No style has been applied to the component "+getComponentName() end_log_err;
			return;
		}
		if(!m_visible) {
			return;
		}
		util::CoordInt coord = getRealCoord();
		BasicStyle::State state = BasicStyle::normal;

		int borderWidth = m_style->topleft(state)->getGlobalBounds().width;
		int borderHeight = m_style->topleft(state)->getGlobalBounds().height;
		m_style->topleft(state)->setPosition(coord.x, coord.y);
		render->draw(*m_style->topleft(state));

		m_style->top(state)->setPosition(coord.x+borderWidth, coord.y);
		m_style->top(state)->setScale(m_width-borderWidth*2, 1.0);
		render->draw(*m_style->top(state));

		m_style->topright(state)->setPosition(coord.x+m_width-borderWidth, coord.y);
		render->draw(*m_style->topright(state));

		m_style->right(state)->setPosition(coord.x+m_width-borderWidth, coord.y+borderHeight);
		m_style->right(state)->setScale(1.0, m_height-borderHeight*2);
		render->draw(*m_style->right(state));

		m_style->botright(state)->setPosition(coord.x+m_width-borderWidth, coord.y+m_height-borderHeight);
		render->draw(*m_style->botright(state));

		m_style->bot(state)->setPosition(coord.x+borderWidth, coord.y+m_height-borderHeight);
		m_style->bot(state)->setScale(m_width-borderWidth*2, 1.0);
		render->draw(*m_style->bot(state));

		m_style->botleft(state)->setPosition(coord.x, coord.y+m_height-borderHeight);
		render->draw(*m_style->botleft(state));

		m_style->left(state)->setPosition(coord.x, coord.y+borderHeight);
		m_style->left(state)->setScale(1.0, m_height-borderHeight*2);
		render->draw(*m_style->left(state));

		m_style->center(state)->setPosition(coord.x+borderWidth, coord.y+borderHeight);
		m_style->center(state)->setScale(m_width-borderWidth*2, m_height-borderHeight*2);
		render->draw(*m_style->center(state));

		m_text.draw(render);
	}

	bool FocusFrame::event(sf::Event* event, bool used) {
		return used;
	}

}


