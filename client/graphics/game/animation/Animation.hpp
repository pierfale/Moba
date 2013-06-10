/*
 * VirtualAnimation.hpp
 *
 *  Created on: 20 avr. 2013
 *      Author: Béni
 */

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <SFML/Graphics.hpp>
#include "../BufferDrawable.hpp"

namespace graphics {

	class Animation : public BufferDrawable {
	public:
		Animation();
		virtual ~Animation();
		bool isDone();

	protected:
		bool m_done;
	};

} /* namespace graphics */
#endif /* ANIMATION_H_ */
