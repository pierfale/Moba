/*
 * Window.hpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/current_function.hpp>
#include <boost/timer.hpp>
#include <string>
#include <vector>
#include <stack>
#include <SFML/Graphics.hpp>

#include "../ImageLoader.hpp"
#include "../../ThreadManager.hpp"
#include "../GuiStyle.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class Component;
	class Container;

	class Window {

	public:
		Window(int width, int height, std::string title);
		void setContentPane(Container* pane);
		void addCallFunction(boost::function<void()> function);
		void setSelectedComponent(Component* component);
		void selectNext();
		std::string getComponentName();
		void run();

		Container* getContentPane();

	private:
		void checkNewContentPane();
		void checkFunctionCall();
		int m_width;
		int m_height;
		std::string m_title;
		sf::RenderWindow* m_window;
		boost::timer m_framesTime;
		int m_framesCount;
		Container* m_root;
		Container* m_rootTmp;
		std::vector<boost::function<void()> > m_callFunction;

	};
}



#endif /* WINDOW_HPP_ */
