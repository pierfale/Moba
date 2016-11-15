/*
 * Skill.cpp
 *
 *  Created on: 25 mai 2013
 *      Author: pierre
 */

#include "Skill.hpp"

Skill::Skill(int id, std::vector<int> parents) : m_id(id), m_parents(parents) {

}

int Skill::getId() {
	return m_id;
}

int Skill::parentSize() {
	return m_parents.size();
}

int Skill::getParent(int i) {
	return m_parents.at(i);
}

