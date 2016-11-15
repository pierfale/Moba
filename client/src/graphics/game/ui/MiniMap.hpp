/*
 * MiniMap.hpp
 *
 *  Created on: 3 juin 2013
 *      Author: pierre
 */

#ifndef MINIMAP_HPP_
#define MINIMAP_HPP_

#include "../../component/Component.hpp"
#include "../../ImageLoader.hpp"
#include "../Gameboard.h"
#include "../../../game/game/GameboardModel.h"

namespace graphics {

	class MiniMap : public Component {

	public:
		MiniMap(std::string image, Gameboard* gameboard);
		void draw(sf::RenderWindow* render);
		bool event(sf::Event* event, bool used);

	private:
		sf::Texture* m_texture;
		Gameboard* m_gameboard;

	};
}


#endif /* MINIMAP_HPP_ */
