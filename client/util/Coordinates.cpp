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

	bool Coordinates::operator==(Coordinates coord){
		return (coord.x == x && coord.y == y);
	}

	bool Coordinates::operator!=(Coordinates coord){
		return !operator==(coord);
	}

	std::string Coordinates::toString(){
		return "[" + util::Cast::intToString(x) + ";" + util::Cast::intToString(y) + "]";
	}

	int Coordinates::compareTo(Coordinates coord) {
		return (abs(x-coord.x)+abs(y-coord.y));
	}

	bool Coordinates::operator<(const Coordinates& other) const {
		if(other.x!=x)
			return other.x<x;
		else
			return other.y<y;
	}

}


