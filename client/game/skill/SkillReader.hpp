/*
 * SkillReader.hpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#ifndef SKILLREADER_HPP_
#define SKILLREADER_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "Skill.hpp"
#include "../../util/Util.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

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
		static boost::shared_ptr<SkillReader> m_instance;
		boost::ptr_vector<Skill> m_skills;
	};
}


#endif /* SPELLREADER_HPP_ */
