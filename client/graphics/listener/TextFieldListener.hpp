/*
 * TextFieldListener.hpp
 *
 *  Created on: 7 avr. 2013
 *      Author: pierre
 */

#ifndef TEXTFIELDLISTENER_HPP_
#define TEXTFIELDLISTENER_HPP_

namespace graphics {

class TextFieldListener {

	public:
	virtual ~TextFieldListener();
	virtual void TextChanged(void* origin);
	virtual void mouseEntered(void* origin);
	virtual void mouseLeft(void* origin);
	virtual void selected(void* origin);
	virtual void unselected(void* origin);
	virtual void enter(void* origin);

	};

}

#endif /* TEXTFIELDLISTENER_HPP_ */
