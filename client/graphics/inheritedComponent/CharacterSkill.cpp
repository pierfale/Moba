/*
 * CharacterSkill.cpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#include "CharacterSkill.hpp"

namespace graphics {

	CharacterSkill::CharacterSkill(game::Player* player) : m_player(player) {
	}

	void CharacterSkill::load() {
		this->setBackgroundColor(sf::Color(30, 30, 30));
		this->setLayout(new PassivLayout());

		std::vector<int> key = game::SkillReader::keySet();

		for(unsigned int i=0; i<key.size(); i++) {
			game::Skill* skill = game::SkillReader::get(key.at(i));
			ButtonImage* tmp = new ButtonImage(skill->getImage(), GUIStyle::button());
			tmp->setCoord(util::Coordinates(skill->getCoord()));
			this->add(tmp);
			std::vector<int> parent = skill->getParents();
			for(unsigned int j = 0; j<parent.size(); j++) {
				if(parent.at(j) != 0) {
					Line* tmp2 = new Line(util::Coordinates(game::SkillReader::get(parent.at(j))->getCoord().x+tmp->getWidth()/2, game::SkillReader::get(parent.at(j))->getCoord().y+tmp->getHeight()),
							util::Coordinates(skill->getCoord().x+tmp->getWidth()/2, skill->getCoord().y), GUIStyle::line());
					this->add(tmp2);
				}
			}
		}
	}

}


