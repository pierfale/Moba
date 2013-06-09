/*
 * ScrollBarStyle.hpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#ifndef SCROLLBARSTYLE_HPP_
#define SCROLLBARSTYLE_HPP_

#include <string>
#include <SFML/Graphics.hpp>
#include "../ImageLoader.hpp"

namespace graphics {

	class ScrollBarStyle {

	public:
		void setBackgroundImage(std::string path);
		void setBarImage(std::string path);

		sf::Sprite* backgroundTop();
		sf::Sprite* backgroundCenter();
		sf::Sprite* backgroundBot();

		sf::Sprite* barTop();
		sf::Sprite* barCenter();
		sf::Sprite* barBot();

	private:
		sf::Texture* m_backgroundImage;
		sf::Texture* m_barImage;

		sf::Sprite m_backgroundTop;
		sf::Sprite m_backgroundCenter;
		sf::Sprite m_backgroundBot;

		sf::Sprite m_barTop;
		sf::Sprite m_barCenter;
		sf::Sprite m_barBot;

	};
}


#endif /* SCROLLBARSTYLE_HPP_ */
