/*
 * Character.hpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include <string>

namespace game {

	class Character {
	public:
		Character(std::string name);

		std::string getName();


	private:
		std::string m_name;
	};
}


#endif /* CHARACTER_HPP_ */
