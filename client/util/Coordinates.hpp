#ifndef COORDINATES_H
#define COORDINATES_H

namespace util {

	class Coordinates {

	public:
		Coordinates();
		Coordinates(int x1, int y1);
		Coordinates(const Coordinates &copy);
		int x, y;
	};

}

#endif
