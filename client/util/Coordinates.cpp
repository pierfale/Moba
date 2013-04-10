/*
 * Coordinates.cpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#include "Coordinates.hpp"

namespace util {

	Coordinates::Coordinates() {
		x = 0;
		y = 0;
	}

	Coordinates::Coordinates(int x1, int y1) {
		x = x1;
		y = y1;
	}

	Coordinates::Coordinates(const Coordinates &copy) {
		x = copy.x;
		y = copy.y;
	}

}


