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
#include <boost/thread.hpp>
#include <boost/current_function.hpp>
#include <string>
#include <stack>
#include <SFML/Graphics.hpp>
#include "../ImageLoader.hpp"
#include "../../ThreadManager.hpp"

namespace graphics {

	class Component;
	class Container;

	class Window {

	public:
		Window(int width, int height, std::string title);
		void setContentPane(Container* pane);
		void setSelectedComponent(Component* component);
		void selectNext();
		ImageLoader* getImageLoader();
		std::string getComponentName();
		void run();

	private:

		int m_width;
		int m_height;
		std::string m_title;
		sf::RenderWindow* m_window;
		Container* m_root;
		ImageLoader m_imageLoader;

	};
}



#endif /* WINDOW_HPP_ */
