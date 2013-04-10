/*
 * Window.cpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#include "Window.hpp"
#include "Component.hpp"
#include "Container.hpp"

namespace graphics {

	Window::Window(int width, int height, std::string title) : m_width(width), m_height(height), m_title(title) {
		client::Log::out("Ref "+util::Cast::ptrToInt(this)+": Create "+getComponentName()+" [title="+title+", width="+util::Cast::intToString(width)+", height="+util::Cast::intToString(height)+"]");
		m_window = NULL;
		m_root = new Container();
		ThreadManager::add(boost::bind(&Window::run, this), BOOST_CURRENT_FUNCTION);
		//boost::thread t(&Window::run, this);
	}

	void Window::setContentPane(Container* pane) {
		m_root = pane;
		pane->setParent(NULL);
		pane->setWindow(this);
		pane->setCoord(util::Coordinates(0,0));
		pane->setSize(m_width, m_height);
		pane->validate();
		client::Log::out("Ref "+util::Cast::ptrToInt(this)+": New ContentPane in "+getComponentName()+" (ref "+util::Cast::ptrToInt(pane)+")");
	}

	void Window::setSelectedComponent(Component* component) {
		if(component->isSelectable()) {
			m_root->setSelected(false);
			component->setSelected(true);
		}
	}

	void Window::selectNext() {
		bool findCurrSelected = false;
		Component* oldSelected;
		boost::ptr_deque<Component> stack;
		stack.push_back(m_root);
		stack.push_back(m_root);
		while(!stack.empty()) {
			Component* curr = stack.pop_back().release();

			if(curr->isContainer()) {
				for(int i=((Container*)curr)->childSize()-1; i>=0; i--) {
					stack.push_back(((Container*)curr)->getChild(i));
				}
			}
			else {
				if(findCurrSelected) {
					if(oldSelected == curr) {
						while(!stack.empty()) {
							stack.pop_back().release();
						}
					}
					if(curr->isSelectable()) {
						setSelectedComponent(curr);
						while(!stack.empty()) {
							stack.pop_back().release();
						}
					}
				}

				else {
					if(curr->isSelected()) {
						oldSelected = curr;
						findCurrSelected = true;
					}
					if(!findCurrSelected && stack.size() == 1) {
						stack.pop_back().release();
					}
				}
			}
		}

	}

	ImageLoader* Window::getImageLoader() {
		return &m_imageLoader;
	}

	std::string Window::getComponentName() {
		return "Window";
	}

	void Window::run() {
		m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), m_title);
		while (m_window->isOpen()) {
			m_imageLoader.process();
			sf::Event event;
			while (m_window->pollEvent(event)) {
				if(event.type == sf::Event::Closed)
						m_window->close();
				else if(event.type == sf::Event::Resized) {
					m_width = m_window->getSize().x;
					m_height = m_window->getSize().y;
					m_window->setView(sf::View(sf::FloatRect(0, 0, m_width, m_height)));
					m_root->setSize(m_width, m_height);
					m_root->validate();
				}
				else if(event.type == sf::Event::TextEntered && event.text.unicode == 9) {
					selectNext();
				}
				else
					m_root->event(&event, false);

			}
			m_window->clear(sf::Color::White);
			m_root->draw(m_window);
			m_window->display();
			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
		}


	}

}
