/*
 * BasicStyle.hpp
 *
 *  Created on: 7 avr. 2013
 *      Author: pierre
 */

#ifndef BASICSTYLE_HPP_
#define BASICSTYLE_HPP_

#include <string>
#include <SFML/Graphics.hpp>
#include "../ImageLoader.hpp"

namespace graphics {

	class BasicStyle {

	public:
		enum State {normal, focus, select, press, disable, StateCount};
		BasicStyle();
		void setBorderImage(std::string path);
		void setCenterImage(std::string path);
		void setFont(sf::Font font);
		void setFontSize(int fontSize);
		void setFontColor(sf::Color color);

		sf::Sprite* center(State s);
		sf::Sprite* topleft(State s);
		sf::Sprite* top(State s);
		sf::Sprite* topright(State s);
		sf::Sprite* right(State s);
		sf::Sprite* botright(State s);
		sf::Sprite* bot(State s);
		sf::Sprite* botleft(State s);
		sf::Sprite* left(State s);
		sf::Font* font();
		int fontSize();
		sf::Color* fontColor();

	private:
		sf::Texture* m_borderImage;
		sf::Texture* m_centerImage;
		sf::Font m_font;
		int m_fontSize;
		sf::Color m_fontColor;

		sf::Sprite m_center[StateCount];
		sf::Sprite m_topleft[StateCount];
		sf::Sprite m_top[StateCount];
		sf::Sprite m_topright[StateCount];
		sf::Sprite m_right[StateCount];
		sf::Sprite m_botright[StateCount];
		sf::Sprite m_bot[StateCount];
		sf::Sprite m_botleft[StateCount];
		sf::Sprite m_left[StateCount];

	};

}

#endif /* BASICSTYLE_HPP_ */
