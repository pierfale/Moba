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

	Skill::Skill(int id, std::string name, std::string describe, std::vector<int> parents, std::string image, util::CoordInt coord, sf::IntRect subrect) : m_subrect(subrect) {
		m_id = id;
		m_name = name;
		m_describe = describe;
		m_parents = parents;
		m_image = image;
		m_coord = coord;
		checkLinkSpell();
	}

	int Skill::getId() {
		return m_id;
	}

	std::string Skill::getImage() {
		return m_image;
	}

	std::string Skill::getTitle() {
		return m_name;
	}

	std::string Skill::getContents() {
		return m_describe;
	}

	util::CoordInt Skill::getCoord() {
		return m_coord;
	}

	std::vector<int> Skill::getParents() {
		return m_parents;
	}

	sf::IntRect Skill::getSubrect() {
		return m_subrect;
	}

	void Skill::checkLinkSpell() {
		unsigned int i=0;
		while(i<m_describe.size()-7) {
			if(m_describe.substr(i, 6) == "SPELL(") {
				unsigned int j=i+6;
				while(j<m_describe.size() && m_describe.at(j) != ')')
					j++;
				if(j<m_describe.size()) {
					std::cout << "=> " << m_describe.substr(i+6, i+6-j) << std::endl;
					Spell* spell = SpellReader::get(util::Cast::stringToInt(m_describe.substr(i+6, i+6-j)));
					if(spell != NULL) {
						m_describe = m_describe.substr(0, i)+"<br/><br/><color=sp>"+spell->getName()+" :</color><br/>"+spell->getContents()+m_describe.substr(j+1);
					}
					return;
				}
			}
			i++;
		}
	}
}


