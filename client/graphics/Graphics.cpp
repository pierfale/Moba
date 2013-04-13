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
		delete window;

	}

}
