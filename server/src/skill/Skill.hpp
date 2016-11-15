/*
 * Skill.hpp
 *
 *  Created on: 25 mai 2013
 *      Author: pierre
 */

#ifndef SKILL_HPP_
#define SKILL_HPP_

#include <vector>

class Skill {

public:
	Skill(int id, std::vector<int> parents);
	int getId();
	int parentSize();
	int getParent(int i);

private:
	int m_id;
	std::vector<int> m_parents;
};


#endif /* SKILL_HPP_ */
