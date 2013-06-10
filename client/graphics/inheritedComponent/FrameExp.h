/*
 * FrameExp.h
 *
 *  Created on: 1 juin 2013
 *      Author: Béni
 */

#ifndef FRAMEEXP_H_
#define FRAMEEXP_H_


#include "boost/timer.hpp"
#include "SFML/Graphics.hpp"

#include "../component/Component.hpp"
#include "../../game/menu/CurrentCharacter.hpp"

namespace graphics {

class FrameExp : public Component {
public:
FrameExp();

void draw(sf::RenderWindow* render);
bool event(sf::Event* event, bool used);
private:
sf::Font m_font;
sf::Texture* m_texture;
int m_expFinal;
boost::timer m_timer;
};

} /* namespace graphics */
#endif /* FRAMEEXP_H_ */
