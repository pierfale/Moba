/*
 * ShotAnim.hpp
 *
 *  Created on: 5 juin 2013
 *      Author: pierre
 */

#ifndef SHOTANIM_HPP_
#define SHOTANIM_HPP_

#include <cmath>
#include "SingleTargetSpellAnim.hpp"


namespace graphics {

	class ShotAnim : public SingleTargetSpellAnim {

	public:
		ShotAnim(game::Character* caster, game::Character* target, std::string image, int nFrame);
		int getValueY();
		void draw(sf::RenderWindow* render, Camera* cam);

	protected:
		sf::Texture* m_texture;
		int m_frame;
		int m_nFrame;
		boost::timer m_timer;
		boost::timer m_lastDraw;
		float m_frameLength;
		float m_speed;
		bool m_first;
		util::CoordFloat m_coord;
	};
}


#endif /* SHOTANIM_HPP_ */
