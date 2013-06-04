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

	std::string Cast::intToHexString(int n) {
		std::stringstream ss;
		ss << std::hex << n;
		return ss.str();
	}

	std::string Cast::floatToString(float n) {
		std::stringstream ss;
		ss << n;
		return ss.str();
	}

	std::string Cast::ptrToString(void* ptr) {
		std::stringstream ss;
		ss << ptr;
		return ss.str();
	}

	int Cast::stringToInt(std::string s) {
		int n;
		std::istringstream ss(s);
		ss >> n;
		return n;
	}
}


