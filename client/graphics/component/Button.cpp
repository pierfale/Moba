/*
 * Button.cpp
 *
 *  Created on: 7 avr. 2013
 *      Author: pierre
 */

#include "Button.hpp"

namespace graphics {

	Button::Button(std::string text, BasicStyle* style) : m_text(text), m_style(style) {
		log_out "Ref "+util::Cast::ptrToString(this)+": Create "+getComponentName()+" [text="+text+", style="+util::Cast::ptrToString(style)+"]" end_log_out;
	}

	Button::~Button() {

	}

	void Button::addListener(ButtonListener* listener) {
		m_listener.push_back(listener);
		log_out "Ref "+util::Cast::ptrToString(this)+": Add listener "+util::Cast::ptrToString(listener)+" in "+getComponentName() end_log_out;
	}

	bool Button::event(sf::Event* event, bool used) {
		if(!m_visible || !m_enable)
			return used;
		util::Coordinates coord = getRealCoord();
		if(event->type == sf::Event::MouseButtonPressed) {
			if(!used && event->mouseButton.x > coord.x && event->mouseButton.x < coord.x+m_width
				&& event->mouseButton.y > coord.y && event->mouseButton.y < coord.y+m_height) {
				if(!m_pressed && m_enable) {
					for(boost::ptr_vector<ButtonListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
						m_window->addCallFunction(boost::bind(&ButtonListener::pressed, &(*it), this));
					}
				}
				m_pressed = true;
				getWindow()->setSelectedComponent(this);
				used = true;
			}
		}
		else if(event->type == sf::Event::MouseButtonReleased) {
			if(m_pressed && m_enable) {
				for(boost::ptr_vector<ButtonListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
					m_window->addCallFunction(boost::bind(&ButtonListener::released, &(*it), this));
				}
			}
			m_pressed = false;
		}
		else if(event->type == sf::Event::MouseMoved) {
			if(!used && event->mouseMove.x > coord.x && event->mouseMove.x < coord.x+m_width
				&& event->mouseMove.y > coord.y && event->mouseMove.y < coord.y+m_height) {
				if(!m_focus && m_enable) {
					for(boost::ptr_vector<ButtonListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
						m_window->addCallFunction(boost::bind(&ButtonListener::mouseEntered, &(*it), this));
					}
				}
				m_focus = true;
				used = true;
			}
			else {
				if(m_focus && m_enable) {
					for(boost::ptr_vector<ButtonListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
						m_window->addCallFunction(boost::bind(&ButtonListener::mouseLeft, &(*it), this));
					}
				}
				m_focus = false;
			}
		}
		else if(event->type == sf::Event::MouseLeft) {
			if(m_focus && m_enable) {
				for(boost::ptr_vector<ButtonListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
					m_window->addCallFunction(boost::bind(&ButtonListener::mouseLeft, &(*it), this));
				}
			}
			m_focus = false;
			if(m_pressed  && m_enable) {
				for(boost::ptr_vector<ButtonListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
					boost::thread t(&ButtonListener::released, &(*it), this);
				}
			}
			m_pressed = false;
		}
		else if(event->type == sf::Event::TextEntered && m_selected) {
			if(event->text.unicode == 13  && m_enable) {
				for(boost::ptr_vector<ButtonListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
					m_window->addCallFunction(boost::bind(&ButtonListener::enter, &(*it), this));
				}
				getWindow()->selectNext();
			}
		}
		return used;
	}

	void Button::setSelected(bool state, bool force) {
		if(force) {
			m_selected = state;
			if(state && !m_selected  && m_enable) {
				for(boost::ptr_vector<ButtonListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
					m_window->addCallFunction(boost::bind(&ButtonListener::selected, &(*it), this));
				}
			}
			else if(!state && m_selected  && m_enable) {
				for(boost::ptr_vector<ButtonListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
					m_window->addCallFunction(boost::bind(&ButtonListener::unselected, &(*it), this));
				}
			}
		}
		else
			m_window->setSelectedComponent(this);
	}

	void Button::setStyle(BasicStyle* style) {
		m_style = style;
	}

	void Button::setMinimalSize() {
		if(m_style == NULL) {
			return;
		}
		sf::Text text(m_text);
		text.setFont(*m_style->font());
		text.setCharacterSize(m_style->fontSize());
		sf::FloatRect textSize = text.getGlobalBounds();
		int borderWidth = m_style->topleft(BasicStyle::normal)->getGlobalBounds().width;
		int borderHeight = m_style->topleft(BasicStyle::normal)->getGlobalBounds().height;
		m_width = borderWidth*2+textSize.width;
		m_height = borderHeight*2+textSize.height;

	}

	void Button::setText(std::string text) {
		m_text = text;
	}

	std::string Button::getText() {
		return m_text;
	}

	std::string Button::getComponentName() {
		return "Button";
	}

	void Button::draw(sf::RenderWindow* render) {
		if(m_style == NULL) {
			log_err "No style has been applied to the component "+getComponentName() end_log_err;
			return;
		}
		if(!m_visible) {
			return;
		}
		util::Coordinates coord = getRealCoord();
		BasicStyle::State state = BasicStyle::normal;

		if(!m_enable)
			state = BasicStyle::disable;
		else if(m_pressed)
			state = BasicStyle::press;
		else if(m_focus)
			state = BasicStyle::focus;
		else if(m_selected)
			state = BasicStyle::select;

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

		sf::Text text(m_text);
		text.setFont(*m_style->font());
		text.setCharacterSize(m_style->fontSize());
		text.setColor(*m_style->fontColor());
		sf::FloatRect textSize = text.getGlobalBounds();
		text.setPosition(coord.x+(m_width-textSize.width)/2,coord.y+(m_height-textSize.height*1.5)/2);
		render->draw(text);

	}


}


