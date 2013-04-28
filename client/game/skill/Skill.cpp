/*
 * Skill.cpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#include "Skill.hpp"

namespace game {

	Skill::Skill() {
		m_id = 0;
		m_name = "";
		m_describe = "";
		m_image = "";
	}

	Skill::Skill(int id, std::string name, std::string describe, std::vector<int> parents, std::string image, util::Coordinates coord) {
		m_id = id;
		m_name = name;
		m_describe = name;
		m_parents = parents;
		m_image = image;
		m_coord = coord;
	}

	int Skill::getId() {
		return m_id;
	}

	std::string Skill::getImage() {
		return m_image;
	}

	util::Coordinates Skill::getCoord() {
		return m_coord;
	}

	std::vector<int> Skill::getParents() {
		return m_parents;
	}
}


