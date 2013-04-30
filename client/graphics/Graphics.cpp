/*
 * Graphics.hpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#include "Graphics.hpp"

namespace graphics {

	boost::shared_ptr<Graphics> Graphics::m_instance;

	Graphics::Graphics() : m_window(NULL) {

	}

	Graphics::~Graphics() {
		delete m_window;
	}

	void Graphics::init() {
		getInstance()->m_window = new Window(800, 600, "Moba");
	}

	void Graphics::run() {
		getInstance()->m_window->run();
	}

	Window* Graphics::getWindow() {
		return getInstance()->m_window;
	}

	Graphics* Graphics::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new Graphics());
		return m_instance.get();
	}

}
