/*
 * Cursor.hpp
 *
 *  Created on: 31 mai 2013
 *      Author: pierre
 */

#ifndef CURSOR_HPP_
#define CURSOR_HPP_

#include <SFML/Graphics.hpp>
#include "ImageLoader.hpp"

#include "../util/Util.hpp"

#define CURSOR_NONE 0
#define CURSOR_GAMENORMAL 1
#define CURSOR_GAMEFOCUS 2

namespace graphics {

	class Cursor {

	public:
		static void load(sf::RenderWindow* render);
		static void set(int type);
		static void draw();

	private:
		Cursor();
		static Cursor* getInstance();
		static boost::shared_ptr<Cursor> m_instance;
		sf::Texture* m_texture;
		sf::RenderWindow* m_render;
		util::CoordInt m_offset;
	};
}


#endif /* CURSOR_HPP_ */
