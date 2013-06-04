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
		util::CoordFloat coord = m_caster->getCoord();
		sf::Sprite sprite;
		sprite.setTexture(*m_texture);
		sprite.setPosition(coord.x-cam->getCoord().x, coord.y-40-cam->getCoord().y);
		sprite.setTextureRect(sf::IntRect(m_frame*m_spriteWidth, 0, m_spriteWidth, m_spriteHeight));
		sprite.setOrigin(40.0, 47.5);
		sprite.setRotation(util::Math::angle(m_target->getCoord(), m_caster->getCoord()));
		render->draw(sprite);
	}

	const int FireballAnim::m_spriteWidth = 120;
	const int FireballAnim::m_spriteHeight = 100;
	const float FireballAnim::m_spriteFrame = 0.1;
	const float FireballAnim::m_speed = 2.0;

	FireballAnim::FireballAnim(game::Character* caster, game::Character* target) : SingleTargetSpellAnim(caster, target) {
		m_frame = 0;
		m_texture = ImageLoader::get("ressources/game/fireball.png");
		m_coord = caster->getCoord();
		m_first = true;
	}

	int FireballAnim::getValueY() {
		return m_coord.y-45;
	}

	void FireballAnim::draw(sf::RenderWindow* render, Camera* cam) {
		if(m_first) {
			m_first = false;
			m_timer.restart();
		}

		if(m_timer.elapsed() > m_spriteFrame) {
			m_frame++;
			m_timer.restart();
		}

		if(m_frame > 3)
			m_frame = 0;

		if(m_coord.x > m_target->getCoord().x)
			m_coord.x = m_coord.x-m_speed > m_target->getCoord().x ? m_coord.x-m_speed : m_target->getCoord().x;
		else if(m_coord.x < m_target->getCoord().x)
			m_coord.x = m_coord.x+m_speed < m_target->getCoord().x ? m_coord.x+m_speed : m_target->getCoord().x;

		if(m_coord.y > m_target->getCoord().y)
			m_coord.y = m_coord.y-m_speed > m_target->getCoord().y ? m_coord.y-m_speed : m_target->getCoord().y;
		else if(m_coord.y < m_target->getCoord().y)
			m_coord.y = m_coord.y+m_speed < m_target->getCoord().y ? m_coord.y+m_speed : m_target->getCoord().y;

		if(m_coord == m_target->getCoord())
			m_done = true;

		sf::Sprite sprite;
		sprite.setTexture(*m_texture);
		sprite.setPosition(m_coord.x, m_coord.y-45);
		sprite.setTextureRect(sf::IntRect(m_frame*m_spriteWidth, 0, m_spriteWidth, m_spriteHeight));
		sprite.setOrigin(50.0, 60.0);
		sprite.setRotation(util::Math::angle(m_target->getCoord(), m_caster->getCoord()));
		render->draw(sprite);
	}
}


