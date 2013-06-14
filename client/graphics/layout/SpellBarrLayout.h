/*
 * SpellBarrLayout.h
 *
 *  Created on: 27 avr. 2013
 *      Author: Béni
 */

#ifndef SPELLBARRLAYOUT_H_
#define SPELLBARRLAYOUT_H_

#include <string>

#include "Layout.hpp"

#define SIZE_ICON 37

namespace graphics {

	class SpellBarrLayout : public Layout{
	public:
		virtual ~SpellBarrLayout();
		void validate();
		std::string getLayoutName();
	};

} /* namespace graphics */
#endif /* SPELLBARRLAYOUT_H_ */
