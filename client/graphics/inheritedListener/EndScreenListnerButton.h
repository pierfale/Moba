/*
 * EndScreenListnerButton.h
 *
 *  Created on: 30 mai 2013
 *      Author: Béni
 */

#ifndef ENDSCREENLISTNERBUTTON_H_
#define ENDSCREENLISTNERBUTTON_H_

#include "../listener/ButtonListener.hpp"
#include "../../graphics/Graphics.hpp"

namespace graphics {

class EndScreenListner_Button : public ButtonListener{
public:
	EndScreenListner_Button();
	virtual ~EndScreenListner_Button();
	void pressed(void* origin);
};

} /* namespace graphics */
#endif /* ENDSCREENLISTNERBUTTON_H_ */
