/*
 * Skill.hpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#ifndef SKILL_HPP_
#define SKILL_HPP_

#include <string>
#include <iostream>

#include "../../util/Util.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace game {

	class Skill {

	public:
		Skill();
		Skill(int id, std::string name, std::string describe, std::vector<int> parents, std::string image, util::Coordinates coord);
		int getId();
		std::string getImage();
		util::Coordinates getCoord();
		std::vector<int> getParents();

	private:
		int m_id;
		std::string m_name;
		std::string m_describe;
		std::vector<int> m_parents;
		std::string m_image;
		util::Coordinates m_coord;

	};
}


#endif
