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
#include <SFML/Graphics.hpp>

#include "../../util/Util.hpp"
#include "../spell/SpellReader.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace game {

	class Skill {

	public:
		Skill();
		Skill(int id, std::string name, std::string describe, std::vector<int> parents, std::string image, util::CoordInt coord, sf::IntRect subrect);
		int getId();
		std::string getImage();
		std::string getTitle();
		std::string getContents();
		util::CoordInt getCoord();
		std::vector<int> getParents();
		sf::IntRect getSubrect();
	private:
		void checkLinkSpell();
		int m_id;
		std::string m_name;
		std::string m_describe;
		std::vector<int> m_parents;
		std::string m_image;
		util::CoordInt m_coord;
		sf::IntRect m_subrect;

	};
}


#endif
