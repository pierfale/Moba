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
#include "game/Gameboard.h"
#include "game/Player.h"

namespace graphics {

	Graphics::Graphics() {

		Window* window = new Window(800, 600, "Moba");
		//GUIStyle::init(window);
		//ConnectionScreen* screen_con = new ConnectionScreen(window);
		Gameboard* g = new Gameboard("Gameboard");
		Player* p = new Player("Client Player");
		Container* c = new Container();
		c->add(g);
		window->setContentPane(c);
		g->load(p);
	}

}
