/*
 * VirtualAnimation.h
 *
 *  Created on: 20 avr. 2013
 *      Author: Béni
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <stdlib.h>

#include "SFML/Graphics.hpp"

#include "../../ImageLoader.hpp"
#include "../Character.h"

namespace graphics {

	class Animation {
	public:
		virtual ~Animation();
		static void draw(sf::RenderWindow* render, Character* caster, Character* target);
		static void drawAutoAttack(sf::RenderWindow* render, Character* caster);
	private:
		Animation();
		void incFrame();
		sf::Sprite* m_sprite;
		sf::Texture* m_texture;
		int m_nbFrame;
		boost::timer m_frame;
		static Animation* getInstance();
		static boost::shared_ptr<Animation> m_instance;
	};

} /* namespace graphics */
#endif /* ANIMATION_H_ */
