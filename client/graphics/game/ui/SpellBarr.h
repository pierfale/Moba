/*
 * SpellBarr.h
 *
 *  Created on: 24 avr. 2013
 *      Author: Béni
 */

#ifndef SPELLBARR_H_
#define SPELLBARR_H_

#include <SFML/Graphics.hpp>
#include <map>

#include "../../GUIStyle.hpp"
#include "../../component/ComponentInclude.hpp"
#include "../../layout/SpellBarrLayout.h"
#include "../../inheritedComponent/ButtonImage.hpp"

#include "../../../game/character/Player.hpp"
#include "../../../game/game/SpellList.hpp"
#include "../../../game/game/CurrentSpell.hpp"
#include "../../Cursor.hpp"

namespace graphics {
	class SpellBarr : public Container{
	public:
		SpellBarr(game::Player* player);
		virtual ~SpellBarr();
		void spellActivate(void* origin);
	private:
		boost::ptr_vector<ButtonImage> m_buttons;
		SpellBarrLayout m_layout;
		std::map<ButtonImage*, game::Spell*> m_buttonSpells;
	};

} /* namespace graphics */
#endif /* SPELLBARR_H_ */
