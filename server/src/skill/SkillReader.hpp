/*
 * SkillReader.hpp
 *
 *  Created on: 25 mai 2013
 *      Author: pierre
 */

#ifndef SKILLREADER_HPP_
#define SKILLREADER_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "Skill.hpp"
#include "../util/Util.hpp"

#include "../log/Log.hpp"

class SkillReader {

public:

	static bool load(std::string path);
	static Skill* get(int id);
	static std::vector<int> keySet();

private:
	SkillReader();
	static SkillReader* getInstance();
	static boost::shared_ptr<SkillReader> m_instance;
	static Skill* evalLine(std::string line);
	static bool isblank(char c);
	boost::ptr_vector<Skill> m_skills;
};

#endif /* SKILLREADER_HPP_ */
