/*
 * MenuInGameButton.h
 *
 *  Created on: 4 mai 2013
 *      Author: Béni
 */

#ifndef MENUINGAMEBUTTON_H_
#define MENUINGAMEBUTTON_H_

#include "../../graphics/component/ComponentInclude.hpp"

namespace graphics {

class UserInterface;

class MenuInGame_Button : public ButtonListener {

public:
	MenuInGame_Button(UserInterface* interface);
	virtual ~MenuInGame_Button();

	void pressed(void* origin);
private:
	UserInterface* m_interface;
};

} /* namespace graphics */
#endif /* MENUINGAMEBUTTON_H_ */
