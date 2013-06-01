/*
 * PathFinding.h
 *
 *  Created on: 29 avr. 2013
 *      Author: Béni
 */

#ifndef PATHFINDING_H_
#define PATHFINDING_H_

#include "Coordinates.hpp"
#include <boost/timer.hpp>
#include <map>
#include <stack>
#include <queue>
#include <iostream>
#include "../log/Log.hpp"

#define D_NONE 0
#define D_NORTH 1
#define D_NORTHEAST 2
#define D_EAST 3
#define D_SOUTHEAST 4
#define D_SOUTH 5
#define D_SOUTHWEST 6
#define D_WEST 7
#define D_NORTHWEST 8
#define DIAG_COST 0.7

namespace util {

	class PathFinding {
	public:
		static std::vector<CoordInt> getPath(CoordInt start, CoordInt goal);
		static std::vector<CoordInt> checkDirection(std::vector<CoordInt> path);
		static float cost(std::vector<CoordInt> path);
		static void printPath(std::vector<CoordInt>);
};

} /* namespace util */
#endif /* PATHFINDING_H_ */
