/*
 * InnerWindow.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#include "InnerWindow.hpp"


namespace graphics {

	InnerWindow::InnerWindow(std::string name, int width, int height, WindowStyle* style) : m_name(name), m_style(style) {
		m_width = width;
		m_height = height;
		m_buttonFocus = false;
		m_buttonPressed = false;
		m_closeable = true;
		client::Log::out("Ref "+util::Cast::ptrToInt(this)+": Create "+getComponentName()+" [name="+name+", width="+util::Cast::intToString(width)+", height="+util::Cast::intToString(height)+", style="+util::Cast::ptrToInt(style)+"]");
	}

	void InnerWindow::addListener(InnerWindowListener* listener) {
		m_listener.push_back(listener);
	}

	bool InnerWindow::event(sf::Event* event, bool used) {
		util::Coordinates coord = Component::getRealCoord();
		if(event->type == sf::Event::MouseButtonPressed) {
			if(m_closeable && event->mouseButton.x >= coord.x+m_width-m_style->topleft()->getGlobalBounds().width-m_style->headerOffset().x &&
					event->mouseButton.x <= coord.x+m_width-m_style->topleft()->getGlobalBounds().width-m_style->headerOffset().x+m_style->button(WindowStyle::normal)->getGlobalBounds().width &&
					event->mouseButton.y >= coord.y+m_style->headerOffset().y+(m_style->topleft()->getGlobalBounds().height-m_style->headerOffset().y-m_style->button(WindowStyle::normal)->getGlobalBounds().height)/2 &&
					event->mouseButton.y <= coord.y+m_style->headerOffset().y+(m_style->topleft()->getGlobalBounds().height-m_style->headerOffset().y-m_style->button(WindowStyle::normal)->getGlobalBounds().height)/2+m_style->button(WindowStyle::normal)->getGlobalBounds().height) {
				m_buttonPressed = true;

			}
			if(!used && event->mouseButton.x > coord.x && event->mouseButton.x < coord.x+m_width
				&& event->mouseButton.y > coord.y && event->mouseButton.y < coord.y+m_style->topleft()->getGlobalBounds().height) {
				if(!m_pressed) {
					for(boost::ptr_vector<InnerWindowListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
						m_window->addCallFunction(boost::bind(&InnerWindowListener::pressed, &(*it), this));
					}
				}
				m_pressed = true;
				getWindow()->setSelectedComponent(this);
				m_originCoord = m_coord;
				m_originMouseCoord = util::Coordinates(event->mouseButton.x, event->mouseButton.y);
				used = true;
			}
			else if(event->mouseButton.x > coord.x && event->mouseButton.x < coord.x+m_width
					&& event->mouseButton.y > coord.y && event->mouseButton.y < coord.y+m_height) {

			}
		}
		else if(event->type == sf::Event::MouseButtonReleased) {
			if(m_pressed) {
				for(boost::ptr_vector<InnerWindowListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
					m_window->addCallFunction(boost::bind(&InnerWindowListener::released, &(*it), this));
				}
			}
			m_pressed = false;
			m_buttonPressed = false;
		}
		else if(event->type == sf::Event::MouseMoved) {
			if(m_pressed) {
				m_coord = util::Coordinates(m_originCoord.x+(event->mouseMove.x-m_originMouseCoord.x), m_originCoord.y+(event->mouseMove.y-m_originMouseCoord.y));
				used = true;
			}
			else if(m_closeable && event->mouseMove.x >= coord.x+m_width-m_style->topleft()->getGlobalBounds().width-m_style->headerOffset().x &&
					event->mouseMove.x <= coord.x+m_width-m_style->topleft()->getGlobalBounds().width-m_style->headerOffset().x+m_style->button(WindowStyle::normal)->getGlobalBounds().width &&
					event->mouseMove.y >= coord.y+m_style->headerOffset().y+(m_style->topleft()->getGlobalBounds().height-m_style->headerOffset().y-m_style->button(WindowStyle::normal)->getGlobalBounds().height)/2 &&
					event->mouseMove.y <= coord.y+m_style->headerOffset().y+(m_style->topleft()->getGlobalBounds().height-m_style->headerOffset().y-m_style->button(WindowStyle::normal)->getGlobalBounds().height)/2+m_style->button(WindowStyle::normal)->getGlobalBounds().height) {
				m_buttonFocus = true;
				m_focus = false;
			}
			else if(!used && event->mouseMove.x > coord.x && event->mouseMove.x < coord.x+m_width
				&& event->mouseMove.y > coord.y && event->mouseMove.y < coord.y+m_height) {
				if(!m_focus) {
					for(boost::ptr_vector<InnerWindowListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
						m_window->addCallFunction(boost::bind(&InnerWindowListener::mouseEntered, &(*it), this));
					}
				}
				m_focus = true;
				m_buttonFocus = false;
				used = true;
			}
			else {
				if(m_focus) {
					for(boost::ptr_vector<InnerWindowListener>::iterator it = m_listener.begin(); it != m_listener.end(); ++it) {
						m_window->addCallFunction(boost::bind(&InnerWindowListener::mouseLeft, &(*it), this));
					}
				}
				m_focus = false;
				m_buttonFocus = false;
			}
		}
		for(boost::ptr_vector<Component>::reverse_iterator it = m_components.rbegin(); it != m_components.rend(); ++it) {
			used = it->event(event, used);
		}
		return used;

	}
	void InnerWindow::setStyle(WindowStyle* style) {
		m_style = style;
	}

	void InnerWindow::setCloseable(bool state) {
		m_closeable = state;
	}

	util::Coordinates InnerWindow::getRealCoord() {
		if(m_parent == NULL)
			return getCoord();
		return util::Coordinates(m_coord.x+m_style->botleft()->getGlobalBounds().width+m_parent->getRealCoord().x, m_coord.y+m_style->topleft()->getGlobalBounds().height+m_parent->getRealCoord().y);
	}

	util::Coordinates InnerWindow::getCoord() {
		return util::Coordinates(m_coord.x+m_style->botleft()->getGlobalBounds().width, m_coord.y+m_style->topleft()->getGlobalBounds().height);
	}

	int InnerWindow::getHeight() {
		return m_height-m_style->botleft()->getGlobalBounds().height-m_style->topleft()->getGlobalBounds().height;
	}

	int InnerWindow::getWidth() {
		return m_width-m_style->botleft()->getGlobalBounds().width*2;
	}

	std::string InnerWindow::getComponentName() {
		return "InnerWindow";
	}

	bool InnerWindow::isSelectable() {
		return false;
	}

	void InnerWindow::draw(sf::RenderWindow* render) {
		if(m_style == NULL)
			return;

		util::Coordinates coord = Component::getRealCoord();

		int topWidth = m_style->topleft()->getGlobalBounds().width;
		int topHeight = m_style->topleft()->getGlobalBounds().height;
		int botWidth = m_style->botleft()->getGlobalBounds().width;
		int botHeight = m_style->botleft()->getGlobalBounds().height;

		m_style->topleft()->setPosition(coord.x, coord.y);
		render->draw(*m_style->topleft());

		m_style->top()->setPosition(coord.x+topWidth, coord.y);
		m_style->top()->setScale(m_width-topWidth*2, 1.0);
		render->draw(*m_style->top());

		m_style->topright()->setPosition(coord.x+m_width-topWidth, coord.y);
		render->draw(*m_style->topright());

		m_style->left()->setPosition(coord.x, coord.y+topHeight);
		m_style->left()->setScale(1.0, m_height-topHeight-botHeight);
		render->draw(*m_style->left());

		m_style->right()->setPosition(coord.x+m_width-botWidth, coord.y+topHeight);
		m_style->right()->setScale(1.0, m_height-topHeight-botHeight);
		render->draw(*m_style->right());

		m_style->botleft()->setPosition(coord.x, coord.y+m_height-botHeight);
		render->draw(*m_style->botleft());

		m_style->bot()->setPosition(coord.x+botWidth, coord.y+m_height-botHeight);
		m_style->bot()->setScale(m_width-botWidth*2, 1.0);
		render->draw(*m_style->bot());

		m_style->botright()->setPosition(coord.x+m_width-botWidth, coord.y+m_height-botHeight);
		render->draw(*m_style->botright());

		m_style->center()->setPosition(coord.x+botWidth, coord.y+topHeight);
		m_style->center()->setScale(m_width-botWidth*2, m_height-topHeight-botHeight);
		render->draw(*m_style->center());

		if(m_closeable) {
			WindowStyle::State buttonState = WindowStyle::normal;
			if(m_buttonFocus)
				buttonState = WindowStyle::focus;
			if(m_buttonPressed)
				buttonState = WindowStyle::press;

			m_style->button(buttonState)->setPosition(coord.x+m_width-topWidth-m_style->headerOffset().x, coord.y+m_style->headerOffset().y+(topHeight-m_style->headerOffset().y-m_style->button(WindowStyle::normal)->getGlobalBounds().height)/2);
			render->draw(*m_style->button(buttonState));
		}

		sf::Text text(m_name);
		text.setFont(*m_style->font());
		text.setCharacterSize(m_style->fontSize());
		text.setColor(*m_style->fontColor());
		sf::FloatRect textSize = text.getGlobalBounds();
		text.setPosition(coord.x+m_style->headerOffset().x+10,coord.y+m_style->headerOffset().y+(topHeight-m_style->headerOffset().y-textSize.height)/2);
		render->draw(text);

		for(boost::ptr_vector<Component>::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			it->draw(render);
		}
	}
}


