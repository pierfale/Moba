/*
 * SpellBarr.h
 *
 *  Created on: 24 avr. 2013
 *      Author: Béni
 */

#ifndef SPELLBARR_H_
#define SPELLBARR_H_

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include "../../GUIStyle.hpp"
#include "../../component/ComponentInclude.hpp"
#include "../../layout/SpellBarrLayout.h"
#include "../../inheritedComponent/ButtonImage.hpp"

#include "../../../game/character/Player.hpp"

namespace graphics {

	class SpellBarr : public Container{
	public:
		SpellBarr(game::Player* player);
		virtual ~SpellBarr();
		bool event(sf::Event* event, bool used);
	private:
		std::vector<ButtonImage> m_buttons;
		SpellBarrLayout m_layout;
	};

} /* namespace graphics */
#endif /* SPELLBARR_H_ */
