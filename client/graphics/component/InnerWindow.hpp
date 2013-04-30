/*
 * InnerWindow.hpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#ifndef INNERWINDOW_HPP_
#define INNERWINDOW_HPP_

#include "Container.hpp"
#include "../style/WindowStyle.hpp"
#include "../listener/InnerWindowListener.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class InnerWindow : public Container {

	public:
		InnerWindow(std::string name, int width, int height, WindowStyle* style=NULL);

		void addListener(InnerWindowListener* listener);
		void draw(sf::RenderWindow* render);
		bool event(sf::Event* event, bool used);
		void setStyle(WindowStyle* style);
		void setCloseable(bool state);

		util::CoordInt getRealCoord();

		util::CoordInt getCoord();
		int getHeight();
		int getWidth();
		std::string getComponentName();

		bool isSelectable();
		void setMinimalSize();

	private:
		std::string m_name;
		WindowStyle* m_style;
		boost::ptr_vector<InnerWindowListener> m_listener;
		util::CoordInt m_originCoord;
		util::CoordInt m_originMouseCoord;

		bool m_closeable;
		bool m_buttonFocus;
		bool m_buttonPressed;

	};

}


#endif /* INNERWINDOW_HPP_ */
