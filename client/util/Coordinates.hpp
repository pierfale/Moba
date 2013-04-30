#ifndef COORDINATES_H
#define COORDINATES_H

#include <cstdlib>
#include <string>
#include "Cast.hpp"

namespace util {

	class Coordinates {

	public:
		Coordinates();
		Coordinates(int x1, int y1);
		Coordinates(const Coordinates &copy);
		int x, y;
		bool operator==(Coordinates coord);
		bool operator!=(Coordinates coord);
		bool operator<(const Coordinates& other) const;
		std::string toString();
		int compareTo(Coordinates coord);
	};

}

#endif
