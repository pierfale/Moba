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
	Graphics::getWindow()->setContentPane(ScreenManager::character());
	network::Packet packet(network::Network::getSocket(), network::PacketType::SESSION_ASKQUITGAME);
	packet.send();
	game::GamePlayerList::clear();
}

} /* namespace graphics */
