/*
 * UserInterface.cpp
 *
 *  Created on: 24 avr. 2013
 *      Author: Béni
 */

#include "UserInterface.h"

namespace graphics {

	UserInterface::UserInterface(game::Player* player) {
		m_spellBarr = new SpellBarr(player);
		add(m_spellBarr);
	}

	UserInterface::~UserInterface() {delete m_spellBarr;}

	void UserInterface::draw(sf::RenderWindow* render) {
		m_spellBarr->setCoord(util::Coordinates(150,150));
		m_spellBarr->draw(render);
	}
	bool UserInterface::event(sf::Event* event, bool used) { return used; }
	void UserInterface::validate() {}

} /* namespace graphics */
