#ifndef COORDINATES_H
#define COORDINATES_H

#include <sstream>
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

		bool operator==(Coordinates<T> coord) {
			return (coord.x == x && coord.y == y);
		}

		bool operator!=(Coordinates<T> coord) {
			return !operator==(coord);
		}

		bool operator <(const Coordinates<T>& coord) const {
			if(x != coord.x)
				return x < coord.x;
			else
				return y < coord.y;
		}

		std::string toString() {
			std::stringstream ss;
			ss << x;
			std::stringstream ss1;
			ss1 << y;
			return "[" + ss.str() + ";" + ss1.str() + "]";
		}

		T x;
		T y;

	};

	typedef Coordinates<int> CoordInt;
	typedef Coordinates<float> CoordFloat;

}

#endif
