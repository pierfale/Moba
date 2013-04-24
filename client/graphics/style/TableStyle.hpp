/*
 * TableStyle.hpp
 *
 *  Created on: 18 avr. 2013
 *      Author: pierre
 */

#ifndef TABLESTYLE_HPP_
#define TABLESTYLE_HPP_

#include <string>
#include <SFML/Graphics.hpp>

#include "../ImageLoader.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class TableStyle {

	public:
		TableStyle();
		void setHeaderBackgroundColor(sf::Color color);
		void setHeaderTextColor(sf::Color color);

		void setBackgroundColor(sf::Color color);
		void setTextColor(sf::Color color);

		void setBackgroundColorFocus(sf::Color color);
		void setBackgroundColorSelect(sf::Color color);

		void setBorderSize(int i);
		void setBorderColor(sf::Color color);

		sf::Color headerBackgroundColor();
		sf::Color headerTextColor();

		sf::Color backgroundColor();
		sf::Color textColor();

		sf::Color backgroundColorFocus();
		sf::Color backgroundColorSelect();

		int borderSize();
		sf::Color borderColor();

	private:
		sf::Color m_headerBackgroundColor;
		sf::Color m_headerTextColor;

		sf::Color m_backgroundColor;
		sf::Color m_textColor;

		sf::Color m_backgroundColorFocus;
		sf::Color m_backgroundColorSelect;

		int m_borderSize;
		sf::Color m_borderColor;
	};
}


#endif /* TABLESTYLE_HPP_ */
