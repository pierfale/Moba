/*
 * StringStyle.hpp
 *
 *  Created on: 26 mai 2013
 *      Author: pierre
 */

#ifndef STRINGSTYLE_HPP_
#define STRINGSTYLE_HPP_

#include <SFML/Graphics.hpp>

namespace graphics {

	class StringStyle {

	public:
		StringStyle();
		StringStyle* copy();

		sf::Color color();
		int size();
		bool isBold();
		bool isItalic();
		bool isUnderline();
		sf::Uint32 style();



		void setColor(sf::Color color);
		void setSize(int size);
		void setBold(bool state);
		void setItalic(bool state);
		void setUnderline(bool state);

	private:
		sf::Color m_color;
		int m_size;

		bool m_bold;
		bool m_italic;
		bool m_underline;
	};
}


#endif /* STRINGSTYLE_HPP_ */
