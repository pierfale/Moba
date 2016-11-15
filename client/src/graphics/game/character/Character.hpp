/*
 * Character.h
 *
 *  Created on: 8 avr. 2013
 *      Author: Béni
 */

#ifndef GRAPHICS_CHARACTER_HPP_
#define GRAPHICS_CHARACTER_HPP_

#include <string>
#include <queue>
#include <math.h>
#include <SFML/Graphics.hpp>

#include "../../../util/Util.hpp"
#include "../../component/ComponentInclude.hpp"
#include "../Camera.h"
#include "../../../game/character/Character.hpp"
#include "../BufferDrawable.hpp"

#define CHARACTER_TIME_BETWEEN_FRAME 0.01
#define CHARACTER_DIAG_RATIO 0.7
#define CASE_SIZE 50

#define CHARACTER_STATE_NOMOVE 0
#define CHARACTER_STATE_GOTO 1
#define CHARACTER_STATE_GOTO_TARGET 2
#define CHARACTER_STATE_GOTO_TARGET_ATTACK 3

namespace graphics {

	class Character : public BufferDrawable {
	public:
		enum Direction{SOUTH, WEST, EAST, NORTH};

		Character(game::Character* model);
		virtual ~Character();

		virtual bool event(sf::Event* event, Camera* cam, bool used);
		int getValueY();
		void draw(sf::RenderWindow* render, Camera* cam);
		game::Character* getModel();
		void setDirection(Direction dir);
		virtual void setState(int state);
		virtual void launchSpell();

	protected:
		game::Character* m_model;
		boost::timer m_timer;
		sf::Texture* m_texture;
		sf::Sprite m_sprite;
		int m_textureWidth;
		int m_textureHeight;

		Direction m_direction;
		int m_nbFrame;
		float m_nextFrame;
		int m_nDirection;
		bool m_focus;
		int m_state;

	};

} /* namespace graphics */
#endif /* CHARACTER_H_ */
