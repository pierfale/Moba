/*
 * ScrollBar.hpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#ifndef SCROLLBAR_HPP_
#define SCROLLBAR_HPP_

#include "Component.hpp"
#include "../style/ScrollBarStyle.hpp"

namespace graphics {

	class ScrollBar : public Component {

	public:
		ScrollBar(ScrollBarStyle* style=NULL);
		void setContentPane(Component* pane);
		util::CoordInt getRealCoord();
		bool event(sf::Event* event, bool used);
		void draw(sf::RenderWindow* render);

		void setScrollDown();

	private:
		ScrollBarStyle* m_style;
		Component* m_pane;
		int m_offsetX;
		int m_offsetY;
		bool isHeightMove;
		util::CoordInt m_mouseInit;
		int m_offsetInitY;

	};
}


#endif /* SCROLLBAR_HPP_ */
