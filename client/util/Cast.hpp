/*
 * Cast.hpp
 *
 *  Created on: 7 avr. 2013
 *      Author: pierre
 */

#ifndef CAST_HPP_
#define CAST_HPP_

#include <string>
#include <sstream>

namespace util {

	class Cast {

	public:
		static std::string intToString(int n);
		static std::string ptrToInt(void* ptr);
		static int stringToInt(std::string s);
	};

}

#endif /* CAST_HPP_ */
