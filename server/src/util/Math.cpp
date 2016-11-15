/*
 * Math.cpp
 *
 *  Created on: 6 mai 2013
 *      Author: pierre
 */

#include "Math.hpp"

namespace util {

	float Math::distance(CoordFloat p1, CoordFloat p2) {
		return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
	}

}


