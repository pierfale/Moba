/*
 * Line.hpp
 *
 *  Created on: 13 avr. 2013
 *      Author: pierre
 */

#ifndef LINE_HPP_
#define LINE_HPP_

#include "Component.hpp"
#include "../style/LineStyle.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class Line : public Component {
	public:
		Line(util::CoordInt origin, util::CoordInt target, LineStyle* style = NULL);
		bool event(sf::Event* event, bool used);
		void draw(sf::RenderWindow* render);

	private:
		util::CoordInt m_origin;
		util::CoordInt m_target;
		LineStyle* m_style;
	};
}


#endif /* LINE_HPP_ */
