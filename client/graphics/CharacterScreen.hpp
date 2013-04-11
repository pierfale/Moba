/*
 * CharacterScreen.hpp
 *
 *  Created on: 9 avr. 2013
 *      Author: pierre
 */

#ifndef CHARACTERSCREEN_HPP_
#define CHARACTERSCREEN_HPP_

#include "component/Container.hpp"
#include "component/ComponentInclude.hpp"
#include "GUIStyle.hpp"
#include "layout/LayoutInclude.hpp"

namespace graphics {

	class CharacterScreen : public Container {

	public:
		CharacterScreen(Window* window);
		void load();

	private:
		Window* m_window;

	};

}


#endif /* CHARACTERSCREEN_HPP_ */
