/*
 * SkillReader.hpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#ifndef SKILLREADER_HPP_
#define SKILLREADER_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include "Skill.hpp"
#include "../../log/Log.hpp"
#include "../../util/Util.hpp"


namespace game {

	class SkillReader {

	public:
		SkillReader();
		bool load(std::string path);
		static Skill* get(int id);
		static std::vector<int> keySet();


	private:
		Skill* evalLine(std::string line);
		bool isblank(char c);
		static SkillReader* getInstance();
		static SkillReader* m_instance;
		boost::ptr_vector<Skill> m_skills;
	};
}


#endif /* SPELLREADER_HPP_ */
