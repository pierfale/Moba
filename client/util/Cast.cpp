/*
 * Cast.cpp
 *
 *  Created on: 7 avr. 2013
 *      Author: pierre
 */

#include "Cast.hpp"

namespace util {

	std::string Cast::intToString(int n) {
		std::stringstream ss;
		ss << n;
		return ss.str();
	}

	std::string Cast::ptrToInt(void* ptr) {
		std::stringstream ss;
		ss << ptr;
		return ss.str();
	}
}


