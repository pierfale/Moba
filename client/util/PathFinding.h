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
#include <queue>
#include "../game/game/GameboardModel.h"

namespace util {

	class PathFinding {
	public:
		static std::vector<Coordinates> getPath(Coordinates start, Coordinates goal);
		static void printPath(std::vector<Coordinates>);
};

} /* namespace util */
#endif /* PATHFINDING_H_ */
