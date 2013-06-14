/*
 * Math.hpp
 *
 *  Created on: 6 mai 2013
 *      Author: pierre
 */

#ifndef MATH_HPP_
#define MATH_HPP_

#include <cmath>
#include "Coordinates.hpp"

namespace util {

	class Math {

	public:
		static float distance(CoordFloat p1, CoordFloat p2);
		static float angle(CoordFloat p1, CoordFloat p2);
	};

}

#endif /* MATH_HPP_ */
