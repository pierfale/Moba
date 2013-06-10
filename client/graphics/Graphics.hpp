/*
 * Graphics.hpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */
#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

#include <boost/shared_ptr.hpp>
#include "component/Window.hpp"
#include "GuiStyle.hpp"

//Log
#include "../log/Log.hpp"
//Debug
#include "../debug/Alloc.hpp"

namespace graphics {

	class Graphics {
	public:
		~Graphics();
		static void init();
		static void run();
		static Window* getWindow();

	private:
		Graphics();
		static Graphics* getInstance();
		static boost::shared_ptr<Graphics> m_instance;
		Window* m_window;
	};
}

#endif
