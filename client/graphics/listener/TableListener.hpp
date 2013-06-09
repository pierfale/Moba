/*
 * TableListener.hpp
 *
 *  Created on: 18 avr. 2013
 *      Author: pierre
 */

#ifndef TABLELISTENER_HPP_
#define TABLELISTENER_HPP_

namespace graphics {

	class TableListener {

	public:
		virtual void rowSelected(void* origin);
	};
}


#endif /* TABLELISTENER_HPP_ */
