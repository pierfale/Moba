/*
 * CreateGameScreen.hpp
 *
 *  Created on: 23 avr. 2013
 *      Author: pierre
 */

#ifndef CREATEGAMESCREEN_HPP_
#define CREATEGAMESCREEN_HPP_

#include "../component/ComponentInclude.hpp"
#include "../GUIStyle.hpp"
#include "../layout/LayoutInclude.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class CreateGameScreen : public Container {

	public:
		 CreateGameScreen();
		~CreateGameScreen();
		void load();
		void buttonChanged(void* origin);

	private:
		Container* m_upContainer;
		Container* m_downContainer;
		Container* m_downPseudoContainer;
		Container* m_downButtonContainer;
		TextField* m_nameTextField;
		Button* m_returnButton;
		Button* m_createButton;

	};
}



#endif /* CREATEGAMESCREEN_HPP_ */
