/*
 * SingleTargetSpellImpl.cpp
 *
 *  Created on: 8 mai 2013
 *      Author: pierre
 */

#include "SingleTargetSpellImpl.hpp"
#include "../../Gameboard.h"

namespace graphics {

	const int AutoAttackAnim::m_spriteWidth = 80;
	const int AutoAttackAnim::m_spriteHeight = 95;
	const float AutoAttackAnim::m_spriteFrame = 0.1;

	AutoAttackAnim::AutoAttackAnim(game::Character* caster, game::Character* target) : SingleTargetSpellAnim(caster, target) {
		m_frame = 0;
		m_first = true;
		m_texture = ImageLoader::get("ressources/game/animSword.png");
	}

	int AutoAttackAnim::getValueY() {
		return m_caster->getCoord().y;
	}

	void AutoAttackAnim::draw(sf::RenderWindow* render, Camera* cam) {
		if(m_first) {
			m_first = false;
			m_timer.restart();
		}

		if(m_timer.elapsed() > m_spriteFrame) {
			m_frame++;
			m_timer.restart();
		}

		if(m_frame > 3) {
			m_done = true;
			return;
		}
		util::CoordFloat coord = m_target->getCoord();
		sf::Sprite sprite;
		sprite.setTexture(*m_texture);
		sprite.setPosition(coord.x, coord.y-40);
		sprite.setTextureRect(sf::IntRect(m_frame*m_spriteWidth, 0, m_spriteWidth, m_spriteHeight));
		sprite.setOrigin(40.0, 47.5);
		sprite.setRotation(util::Math::angle(m_caster->getCoord(), m_target->getCoord()));
		render->draw(sprite);
	}
}


