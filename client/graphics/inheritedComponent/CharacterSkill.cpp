/*
 * CharacterSkill.cpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#include "CharacterSkill.hpp"
#include "../inheritedListener/CharacterSkill_SkillListener.hpp"

namespace graphics {

	CharacterSkill::CharacterSkill(game::Player* player) : m_player(player) {

	}

	CharacterSkill::~CharacterSkill() {
		for(std::map<int, ButtonImage*>::iterator it = m_button.begin(); it != m_button.end(); ++it) {
			delete it->second;
		}
	}

	void CharacterSkill::load() {
		network::Packet packet(network::Network::getSocket(), network::PacketType::SESSION_ASKALLSKILL);
		packet.send();

		this->setBackgroundColor(sf::Color(30, 30, 30));
		this->setLayout(new PassivLayout());

		std::vector<int> key = game::SkillReader::keySet();
		for(unsigned int i=0; i<key.size(); i++) {
			game::Skill* skill = game::SkillReader::get(key.at(i));
			ButtonImage* tmp = new ButtonImage(skill->getImage(), skill->getSubrect(), GUIStyle::buttonImage());
			tmp->setCoord(util::CoordInt(skill->getCoord()));
			tmp->setFocusFrame(new FocusFrame(skill->getTitle(), skill->getContents(), GUIStyle::focusFrame()));
			tmp->addListener(new CharacterSkill_SkillListener(this));
			tmp->setSelectable(false);
			this->add(tmp);
			m_button[skill->getId()] = tmp;
			m_buttonReverse[tmp] = skill->getId();
			std::vector<int> parent = skill->getParents();
			for(unsigned int j = 0; j<parent.size(); j++) {
				if(parent.at(j) != 0) {
					Line* tmp2 = new Line(util::CoordInt(game::SkillReader::get(parent.at(j))->getCoord().x+tmp->getWidth()/2, game::SkillReader::get(parent.at(j))->getCoord().y+tmp->getHeight()),
							util::CoordInt(skill->getCoord().x+tmp->getWidth()/2, skill->getCoord().y), GUIStyle::line());
					this->add(tmp2);
					m_line.push_back(tmp2);
				}
			}
		}
		checkDisableSkill();
	}

	std::string CharacterSkill::getComponentName() {
		return "CharacterSkill";
	}

	std::string CharacterSkill::getName() {
		return "CharacterSkill";
	}

	void CharacterSkill::setActiveSkill(int id) {
		m_button[id]->setSelected(true, true);
		checkDisableSkill();

	}

	void CharacterSkill::checkDisableSkill() {

		std::vector<int> keyset = game::SkillReader::keySet();
		for(unsigned int i=0; i<keyset.size(); i++) {
			game::Skill* skill = game::SkillReader::get(keyset.at(i));
			if(skill != NULL) {
				std::vector<int> parents = skill->getParents();
				bool enable = false;
				for(unsigned int j=0; !enable && j<parents.size(); j++) {
					if(parents.at(j) == 0)
						enable = true;
					game::Skill* skill2 = game::SkillReader::get(parents.at(j));
					if(skill2 != NULL) {
						if(m_button[skill2->getId()]->isSelected())
							enable = true;
					}
				}
				m_button[skill->getId()]->setEnable(enable);
			}

		}
	}

	void CharacterSkill::skillPressed(void* origin) {
		network::Packet packet(network::Network::getSocket(), network::PacketType::SESSION_ASKSKILL);
		packet << m_buttonReverse[(ButtonImage*)origin];
		packet.send();
	}

}


