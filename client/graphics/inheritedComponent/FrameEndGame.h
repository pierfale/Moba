/*
 * FrameEndGame.h
 *
 *  Created on: 23 mai 2013
 *      Author: Béni
 */

#ifndef FRAMEENDGAME_H_
#define FRAMEENDGAME_H_

#include "SFML/Graphics.hpp"

#include "../../util/Cast.hpp"

#include "../component/ComponentInclude.hpp"
#include "../../game/game/GameboardModel.h"
#include "../../game/character/Player.hpp"
#include "../../game/menu/CurrentCharacter.hpp"
#include "../../game/menu/PlayerList.hpp"
#include "../ImageLoader.hpp"

namespace graphics {

class FrameEndGame : public Component {
public:
	FrameEndGame();

	void draw(sf::RenderWindow* render);
	bool event(sf::Event* event, bool used);

	void drawHeader(sf::RenderWindow* render);
	void drawPlayerInfo(sf::RenderWindow* render, game::Player* player, int index);

	virtual ~FrameEndGame();
private:
	sf::Texture* m_texture_background;
	sf::Texture* m_texture_icon;
	sf::Font m_font;
};

} /* namespace graphics */
#endif /* FRAMEENDGAME_H_ */
