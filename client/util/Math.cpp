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

	float Math::angle(CoordFloat p1, CoordFloat p2) {
		float angle = atan2(p1.y - p2.y, p1.x - p2.x)* 180 / M_PI;
		if(angle < 0)
			return 360.0 + angle;
		return angle;
	}

}


