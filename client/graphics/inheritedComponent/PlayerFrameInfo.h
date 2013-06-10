/*
 * PlayerFrameInfo.h
 *
 *  Created on: 2 mai 2013
 *      Author: Béni
 */

#ifndef PLAYERFRAMEINFO_H_
#define PLAYERFRAMEINFO_H_

#include <SFML/Graphics.hpp>

#include "../../util/Cast.hpp"

#include "../component/Component.hpp"
#include "../../game/character/Player.hpp"

namespace graphics {

class CurrentCharacter;

	class PlayerFrameInfo : public Component{
	public:
		PlayerFrameInfo();
		PlayerFrameInfo(game::Character* chara);

		void setPlayer(game::Character* chara);
		void setScale(float scale);

		void draw(sf::RenderWindow* render);
		bool event(sf::Event* event, bool used);

	private:
		game::Character* m_char;
		sf::Font m_font;
		sf::Texture* m_textureBackground,* m_textureIcon;
		float m_scale;
		int m_offsetX, m_offsetY;
	};

} /* namespace graphics */
#endif /* PLAYERFRAMEINFO_H_ */
