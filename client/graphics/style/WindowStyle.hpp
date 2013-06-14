/*
 * WindowStyle.hpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#ifndef WINDOWSTYLE_HPP_
#define WINDOWSTYLE_HPP_

#include <string>
#include <SFML/Graphics.hpp>

#include "../../util/Util.hpp"
#include "../ImageLoader.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class WindowStyle {
	public:
		enum State {normal, focus, press, StateCount};
		WindowStyle();
		void setBotImage(std::string path);
		void setTopImage(std::string path);
		void setCenterImage(std::string path);
		void setButtonImage(std::string path);

		void setFont(sf::Font font);
		void setFontSize(int fontSize);
		void setFontColor(sf::Color color);
		void setHeaderOffset(util::CoordInt coord);

		sf::Sprite* topleft();
		sf::Sprite* top();
		sf::Sprite* topright();

		sf::Sprite* button(State s);

		sf::Sprite* center();

		sf::Sprite* botright();
		sf::Sprite* bot();
		sf::Sprite* botleft();
		sf::Sprite* left();
		sf::Sprite* right ();

		sf::Font* font();
		int fontSize();
		sf::Color* fontColor();
		util::CoordInt headerOffset();

	private:
		sf::Texture* m_botImage;
		sf::Texture* m_topImage;
		sf::Texture* m_centerImage;
		sf::Texture* m_buttonImage;

		sf::Font m_font;
		int m_fontSize;
		sf::Color m_fontColor;
		util::CoordInt m_headerOffset;

		sf::Sprite m_button[StateCount];

		sf::Sprite m_center;
		sf::Sprite m_topleft;
		sf::Sprite m_top;
		sf::Sprite m_topright;
		sf::Sprite m_right;
		sf::Sprite m_botright;
		sf::Sprite m_bot;
		sf::Sprite m_botleft;
		sf::Sprite m_left;
	};

}

#endif /* WINDOWSTYLE_HPP_ */
