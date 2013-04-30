/*
 * UserInterface.h
 *
 *  Created on: 24 avr. 2013
 *      Author: Béni
 */

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "SpellBarr.h"
#include "../../../util/Coordinates.hpp"
#include "../../../game/character/Player.hpp"
#include "../../component/ComponentInclude.hpp"

namespace graphics {

class UserInterface : public Container {
	public:
		UserInterface(game::Player* player);
		virtual ~UserInterface();

		void draw(sf::RenderWindow* render);
		bool event(sf::Event* event, bool used);
		void validate();
	private:
		SpellBarr* m_spellBarr;
	};

} /* namespace graphics */
#endif /* USERINTERFACE_H_ */
