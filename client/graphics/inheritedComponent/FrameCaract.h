/*
 * FrameCaract.h
 *
 *  Created on: 5 juin 2013
 *      Author: Béni
 */

#ifndef FRAMECARACT_H_
#define FRAMECARACT_H_

#include <SFML/Graphics.hpp>

#include "../component/ComponentInclude.hpp"
#include "../../game/character/Character.hpp"

namespace graphics {

class FrameCaract : public Component{
public:
	FrameCaract(game::Character* chara);
	virtual ~FrameCaract();

	void draw(sf::RenderWindow* render);
	bool event(sf::Event* event, bool used);
private:
	game::Character* m_char;
	sf::Font m_font;
	sf::Texture* m_textureBackground,* m_textureIcon;
};

} /* namespace graphics */
#endif /* FRAMECARACT_H_ */
