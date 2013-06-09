/*
 * LifeLoseAnim.hpp
 *
 *  Created on: 5 juin 2013
 *      Author: pierre
 */

#ifndef LIFELOSEANIM_HPP_
#define LIFELOSEANIM_HPP_

#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "../../game/character/Player.hpp"

namespace graphics {

	class LifeLoseAnim : public Animation {

	public:
		LifeLoseAnim(bool isPhysical, int n, game::Player* player);
		int getValueY();
		void draw(sf::RenderWindow* render, Camera* cam);

	private:
		sf::Text m_text;
		game::Player* m_player;
		float m_y;
		boost::timer m_timer;
		bool m_first;
	};
}


#endif /* LIFELOSEANIM_HPP_ */
