/*
 * NewCharacterScreen.hpp
 *
 *  Created on: 14 avr. 2013
 *      Author: pierre
 */

#ifndef NEWCHARACTERSCREEN_HPP_
#define NEWCHARACTERSCREEN_HPP_

#include "../component/ComponentInclude.hpp"
#include "../GUIStyle.hpp"
#include "../layout/LayoutInclude.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class NewCharacterScreen : public Container {

	public:
		NewCharacterScreen();
		~NewCharacterScreen();
		void load();
		void buttonChanged(void* origin);

	private:
		Container* m_upContainer;
		Container* m_downContainer;
		Container* m_downPseudoContainer;
		Container* m_downButtonContainer;
		TextField* m_pseudoTextField;
		Button* m_returnButton;
		Button* m_createButton;

	};
}


#endif /* NEWCHARACTERSCREEN_HPP_ */
