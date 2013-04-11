/*
 * Graphics.hpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#include "Graphics.hpp"
#include "component/Window.hpp"
#include "ConnectionScreen.hpp"
#include "GuiStyle.hpp"

namespace graphics {

	Graphics::Graphics() {

		Window* window = new Window(800, 600, "Moba");
		GUIStyle::init(window);
		ConnectionScreen* screen_con = new ConnectionScreen(window);
		window->setContentPane(screen_con);
		screen_con->load();
	}

}
