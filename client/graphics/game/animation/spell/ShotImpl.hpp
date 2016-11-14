/*
 * ShotImpl.hpp
 *
 *  Created on: 5 juin 2013
 *      Author: pierre
 */

#ifndef SHOTIMPL_HPP_
#define SHOTIMPL_HPP_

#include "ShotAnim.hpp"
#include <iostream>

namespace graphics {

	class FireBallAnim : public ShotAnim {

	public:
		FireBallAnim(game::Character* caster, game::Character* target) : ShotAnim(caster, target, "ressources/game/fireball.png", 4) {

		}

	};

	class ArrowAnim : public ShotAnim {

	public:
		ArrowAnim(game::Character* caster, game::Character* target) : ShotAnim(caster, target, "ressources/game/arrow.png", 1) {
			m_speed = 500;
		}

	};
}


#endif /* SHOTIMPL_HPP_ */
