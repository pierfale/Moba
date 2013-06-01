/*
 * EndScreenListnerButton.cpp
 *
 *  Created on: 30 mai 2013
 *      Author: Béni
 */

#include "EndScreenListnerButton.h"
#include "../../graphics/screen/ScreenManager.hpp"

namespace graphics {

EndScreenListner_Button::EndScreenListner_Button() {}
EndScreenListner_Button::~EndScreenListner_Button() {}

void EndScreenListner_Button::pressed(void* origin) {
	graphics::Graphics::getWindow()->setContentPane(ScreenManager::connection());
}

} /* namespace graphics */
