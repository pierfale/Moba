/*
 * Label.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#include "Label.hpp"

namespace graphics {

	Label::Label(std::string text, BasicStyle* style) : m_text(text), m_style(style), m_align(alignLeft) {
		client::Log::out("Ref "+util::Cast::ptrToInt(this)+": Create "+getComponentName()+" [text="+text+", style="+util::Cast::ptrToInt(style)+"]");
	}


	void Label::addListener(LabelListener* listener) {
		m_listener.push_back(listener);
	}

	bool Label::event(sf::Event* event, bool used) {
		util::Coordinates coord = getRealCoord();
		if(event->type == sf::Event::MouseMoved) {
			if(!used && event->mouseMove.x > coord.x && event->mouseMove.x < coord.x+m_width
				&& event->mouseMove.y > coord.y && event->mouseMove.y < coord.y+m_height) {
				if(!m_focus) {
					for(boost::ptr_vector<LabelListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
						it->mouseEntered(this);
					}
				}
				m_focus = true;
				used = true;
			}
			else {
				if(m_focus) {
					for(boost::ptr_vector<LabelListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
						it->mouseLeft(this);
					}
				}
				m_focus = false;
			}
		}
		else if(event->type == sf::Event::MouseLeft) {
			if(m_focus) {
				for(boost::ptr_vector<LabelListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
					it->mouseLeft(this);
				}
			}
			m_focus = false;
		}
		return used;
	}

	void Label::setStyle(BasicStyle* style) {
		m_style = style;
	}

	void Label::setMinimalSize() {
		if(m_style == NULL) {
			return;
		}
		sf::Text text(m_text);
		text.setFont(*m_style->font());
		text.setCharacterSize(m_style->fontSize());
		sf::FloatRect textSize = text.getGlobalBounds();
		m_width = textSize.width;
		m_height = textSize.height;
	}

	void Label::setAlign(Align align) {
		m_align = align;
	}

	void Label::setText(std::string text) {
		m_text = text;
	}

	std::string Label::getText() {
		return m_text;
	}

	std::string Label::getComponentName() {
		return "Label";
	}

	bool Label::isSelectable() {
		return false;
	}

	void Label::draw(sf::RenderWindow* render) {
		if(m_style == NULL) {
			return;
		}
		util::Coordinates coord = getRealCoord();
		sf::Text text(m_text);
		text.setFont(*m_style->font());
		text.setCharacterSize(m_style->fontSize());
		text.setColor(*m_style->fontColor());
		sf::FloatRect textSize = text.getGlobalBounds();
		if(m_align == alignLeft)
			text.setPosition(coord.x,coord.y+(m_height-textSize.height*1.5)/2);
		else if(m_align == alignCenter)
			text.setPosition(coord.x+(m_width-textSize.width)/2,coord.y+(m_height-textSize.height*1.5)/2);
		else
			text.setPosition(coord.x+m_width-textSize.width,coord.y+(m_height-textSize.height*1.5)/2);
		render->draw(text);
	}
}


