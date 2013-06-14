/*
 * Cursor.cpp
 *
 *  Created on: 31 mai 2013
 *      Author: pierre
 */

#include "Cursor.hpp"

namespace graphics {

	boost::shared_ptr<Cursor> Cursor::m_instance;

	Cursor::Cursor() {
		m_render = NULL;
		m_texture = NULL;
	}

	void Cursor::load(sf::RenderWindow* render) {
		getInstance()->m_render = render;
	}

	void Cursor::set(int type) {
		if(getInstance()->m_render == NULL)
			return;

		switch(type) {
		case CURSOR_NONE:
			getInstance()->m_texture = NULL;
			break;
		case CURSOR_GAMENORMAL:
			getInstance()->m_texture = ImageLoader::get("ressources/game/cursor1.png");
			getInstance()->m_offset = util::CoordInt(0,0);
			break;
		case CURSOR_GAMEFOCUS:
			getInstance()->m_texture = ImageLoader::get("ressources/game/cursor2.png");
			getInstance()->m_offset = util::CoordInt(12,12);
			break;
		}
	}

	void Cursor::draw() {
		if(getInstance()->m_texture != NULL) {
			getInstance()->m_render->setMouseCursorVisible(false);
			sf::Sprite render;
			render.setTexture(*getInstance()->m_texture);
			render.setPosition(sf::Mouse::getPosition(*getInstance()->m_render).x-getInstance()->m_offset.x, sf::Mouse::getPosition(*getInstance()->m_render).y-getInstance()->m_offset.y);
			getInstance()->m_render->draw(render);
		}
		else
			getInstance()->m_render->setMouseCursorVisible(true);
	}

	Cursor* Cursor::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new Cursor());
		return m_instance.get();
	}
}


