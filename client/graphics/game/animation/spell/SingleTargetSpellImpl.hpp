/*
 * SingleTargetSpellImpl.hpp
 *
 *  Created on: 8 mai 2013
 *      Author: pierre
 */

#ifndef SINGLETARGETSPELLIMPL_HPP_
#define SINGLETARGETSPELLIMPL_HPP_

#include "SingleTargetSpellAnim.hpp"
#include <boost/timer.hpp>

namespace graphics {

	class AutoAttackAnim : public SingleTargetSpellAnim {

	public:
		AutoAttackAnim(game::Character* caster, game::Character* target);
		int getValueY();
		void draw(sf::RenderWindow* render, Camera* cam);

	private:
		static const int m_spriteWidth;
		static const int m_spriteHeight;
		static const float m_spriteFrame;

		sf::Texture* m_texture;
		int m_frame;
		boost::timer m_timer;
		bool m_first;
	};

	class FireballAnim : public SingleTargetSpellAnim {

	public:
		FireballAnim(game::Character* caster, game::Character* target);
		int getValueY();
		void draw(sf::RenderWindow* render, Camera* cam);

	private:
		static const int m_spriteWidth;
		static const int m_spriteHeight;
		static const float m_spriteFrame;
		static const float m_speed;

		sf::Texture* m_texture;
		int m_frame;
		boost::timer m_timer;
		bool m_first;
		util::CoordFloat m_coord;
	};
}



#endif /* SINGLETARGETSPELLIMPL_HPP_ */
