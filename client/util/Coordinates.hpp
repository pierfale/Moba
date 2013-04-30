#ifndef COORDINATES_H
#define COORDINATES_H

#include <string>
#include "Cast.hpp"

namespace util {

	template <typename T>
	class Coordinates {

	public:
		Coordinates() {
			x = 0;
			y = 0;
		}

		Coordinates(T x1, T y1) {
			x = x1;
			y = y1;
		}

		Coordinates(const Coordinates<T> &copy) {
			x = copy.x;
			y = copy.y;
		}

		bool operator==(Coordinates coord) {
			return (coord.x == x && coord.y == y);
		}

		bool operator!=(Coordinates coord) {
			return !operator==(coord);
		}

		std::string toString() {
			return "[" + util::Cast::intToString(x) + ";" + util::Cast::intToString(y) + "]";
		}

		T x;
		T y;
	};

	typedef Coordinates<int> CoordInt;
	typedef Coordinates<float> CoordFloat;

}

#endif
