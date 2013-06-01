/*
 * SingleTargetSpell.hpp
 *
 *  Created on: 8 mai 2013
 *      Author: pierre
 */

#ifndef SINGLETARGETSPELL_HPP_
#define SINGLETARGETSPELL_HPP_

#include "../Animation.hpp"
#include "../../../game/character/Character.hpp"

namespace graphics {

	class SingleTargetSpellAnim : public Animation {

	public:
		SingleTargetSpellAnim(game::Character* caster, game::Character* target);

	protected:
		game::Character* m_caster;
		game::Character* m_target;
	};
}


#endif /* SINGLETARGETSPELL_HPP_ */
