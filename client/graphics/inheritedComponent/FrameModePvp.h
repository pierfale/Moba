/*
 * FrameModePvp.h
 *
 *  Created on: 23 mai 2013
 *      Author: Béni
 */

#ifndef FRAMEMODEPVP_H_
#define FRAMEMODEPVP_H_

#include "SFML/Graphics.hpp"
#include "boost/timer.hpp"

#include "VirtualFrameMode.h"
#include "../../game/game/GameboardModel.h"
#include "../../game/menu/CurrentCharacter.hpp"

namespace graphics {

class FrameModePvp : public VirtualFrameMode {
public:
	FrameModePvp();
	virtual ~FrameModePvp();
	void draw(sf::RenderWindow* render);
	bool event(sf::Event* event, bool used);
	void validate();
private:
	boost::timer m_timer;
	sf::Font m_font;
	sf::Texture* m_texture_background;

};

} /* namespace graphics */
#endif /* FRAMEMODEPVP_H_ */
