/*
 * Window.cpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#include "Window.hpp"
#include "Component.hpp"
#include "Container.hpp"
#include "../screen/ScreenManager.hpp"

namespace graphics {

	Window::Window(int width, int height, std::string title) : m_width(width), m_height(height), m_title(title) {
		log_out "Ref "+util::Cast::ptrToString(this)+": Create "+getComponentName()+" [title="+title+", width="+util::Cast::intToString(width)+", height="+util::Cast::intToString(height)+"]" end_log_out;
		m_window = NULL;
		m_root = NULL;
		m_rootTmp = NULL;
		m_framesCount = 0;
	}

	void Window::setContentPane(Container* pane) {
		m_rootTmp = pane;
	}

	void Window::addCallFunction(boost::function<void()> function) {
		m_callFunction.push_back(function);
	}

	void Window::checkNewContentPane() {
		if(m_rootTmp != NULL) {
			Container* old = m_root;
			m_root = m_rootTmp;
			m_root->setParent(NULL);
			m_root->setWindow(this);
			m_root->setCoord(util::Coordinates(0,0));
			m_root->setSize(m_width, m_height);
			m_root->validate();
			log_out "Ref "+util::Cast::ptrToString(this)+": New ContentPane in "+getComponentName()+" (ref "+util::Cast::ptrToString(m_root)+")" end_log_out;
			//std::cout << m_root->toString(true) << std::endl;
			delete old;
			m_rootTmp = NULL;
		}
	}

	void Window::checkFunctionCall() {
		 for (std::vector<boost::function<void()> >::iterator it = m_callFunction.begin() ; it != m_callFunction.end(); ++it)
			 (*it)();
		 m_callFunction.clear();
	}
	void Window::setSelectedComponent(Component* component) {
		if(component == NULL) {
			m_root->setSelected(false, true);
		}
		else if(component->isSelectable()) {
			m_root->setSelected(false, true);
			component->setSelected(true, true);
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

	std::string Window::getComponentName() {
		return "Window";
	}

	Container* Window::getContentPane() {
		if(m_rootTmp != NULL)
			return m_rootTmp;
		return m_root;
	}

	void Window::run() {
		m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), m_title);
		GUIStyle::init();
		setContentPane(ScreenManager::connection());
		while (m_window->isOpen()) {
			checkNewContentPane();
			checkFunctionCall();
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
			//ImageLoader::process();
			m_window->clear(sf::Color::White);
			m_root->draw(m_window);
			m_window->display();
			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
			m_framesCount++;
			if(m_framesTime.elapsed() >= 1.0) {
				m_window->setTitle(m_title+" | fps : "+util::Cast::intToString(m_framesCount));
				m_framesTime.restart();
				m_framesCount = 0;
			}
		}

	}

}
