/*
 * VirtualAnimation.cpp
 *
 *  Created on: 20 avr. 2013
 *      Author: Béni
 */

#include "Animation.h"

namespace graphics {

	boost::shared_ptr<Animation> Animation::m_instance;

	Animation::Animation() : m_nbFrame(0) {m_sprite = NULL; m_texture = NULL;}
	Animation::~Animation() { free(m_sprite); }

	void Animation::draw(sf::RenderWindow* render, Character* caster, Character* target) {
		getInstance()->drawAutoAttack(render, caster);
	}

	void Animation::incFrame() {if (getInstance()->m_nbFrame == 3) getInstance()->m_nbFrame = 0; else getInstance()->m_nbFrame++;}

	void Animation::drawAutoAttack(sf::RenderWindow* render, Character* caster) {
		if (getInstance()->m_frame.elapsed() > caster->getPlayerModel()->getStat()->attackSpeed()) {
			getInstance()->m_frame.restart();getInstance()->incFrame();
		}
		getInstance()->m_texture = ImageLoader::get("ressources/game/animSword.png");
		getInstance()->m_sprite = new sf::Sprite();
		getInstance()->m_sprite->setTexture(*(getInstance()->m_texture));
		sf::Rect<int> spriteZone(getInstance()->m_nbFrame*60,caster->getDirection()*95,60,95);
		getInstance()->m_sprite->setTextureRect(spriteZone);
		getInstance()->m_sprite->setPosition(caster->getPlayerModel()->getCoord().x,caster->getPlayerModel()->getCoord().y);
		render->draw(*getInstance()->m_sprite);
		delete getInstance()->m_sprite;
	}

	Animation* Animation::getInstance() {
		if(m_instance.get() == NULL)
					m_instance.reset(new Animation());
				return m_instance.get();

	}


} /* namespace graphics */
