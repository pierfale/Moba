/*
 * SkillReader.cpp
 *
 *  Created on: 12 avr. 2013
 *      Author: pierre
 */

#include "SkillReader.hpp"

namespace game {

	boost::shared_ptr<SkillReader> SkillReader::m_instance;

	SkillReader::SkillReader() {

	}

	bool SkillReader::load(std::string path) {
		std::ifstream file(path.c_str(), std::ios::in);
		if(!file) {
			log_err "Unable to open "+path end_log_err;
			return false;
		}
		std::string line;
		while(std::getline(file, line))  {
			Skill* skill = evalLine(line);
			if(skill != NULL) {
				getInstance()->m_skills.push_back(skill);
			}
		}

		file.close();
		return true;
	}

	Skill* SkillReader::evalLine(std::string line) {
		unsigned int cursor = 0;
		std::vector<std::string> args;
		for(int i=0; i<11; i++) {
 			while(cursor < line.length() && isblank(line.at(cursor))) {
				cursor++;
			}
			int beg = cursor;
			if(cursor == line.length())
				return NULL;
			if(line.at(cursor) == '"') {
				cursor++;
				while(cursor < line.length() && line.at(cursor) != '"') {
					cursor++;
				}
				if(cursor == line.length())
					return NULL;
				args.push_back(line.substr(beg+1, cursor-beg-1));
				cursor += 2;
			}
			else {
				if(cursor >= line.length())
					return NULL;
				while(cursor < line.length() && !isblank(line.at(cursor))) {
					cursor++;
				}
				args.push_back(line.substr(beg, cursor-beg));
				cursor++;
			}
		}

		std::vector<int> parents;
		cursor = 0;
		int beg = 0;
		while(cursor < args.at(3).length()) {
			if(args.at(3).at(cursor) == ',') {
				parents.push_back(util::Cast::stringToInt(args.at(3).substr(beg, cursor-beg)));
				beg = cursor+1;
			}
			cursor++;
		}
		parents.push_back(util::Cast::stringToInt(args.at(3).substr(beg, cursor-beg)));
		return new Skill(util::Cast::stringToInt(args.at(0)), args.at(1), args.at(2), parents, args.at(4), util::CoordInt(util::Cast::stringToInt(args.at(5)), util::Cast::stringToInt(args.at(6))), sf::IntRect(util::Cast::stringToInt(args.at(7)), util::Cast::stringToInt(args.at(8)), util::Cast::stringToInt(args.at(9)), util::Cast::stringToInt(args.at(10))));
	}

	bool SkillReader::isblank(char c) {
		char blank [] = {' ', '\t'};
		for(int i=0; i<2; i++) {
			if(c == blank[i])
				return true;
		}
		return false;
	}

	Skill* SkillReader::get(int id) {
		for(boost::ptr_vector<Skill>::iterator it = getInstance()->m_skills.begin(); it != getInstance()->m_skills.end(); ++it) {
			if(it->getId() == id)
				return &(*it);
		}
		return NULL;
	}

	std::vector<int> SkillReader::keySet() {
		std::vector<int> v;
		for(boost::ptr_vector<Skill>::iterator it = getInstance()->m_skills.begin(); it != getInstance()->m_skills.end(); ++it) {
			v.push_back(it->getId());
		}
		return v;
	}

	SkillReader* SkillReader::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new SkillReader());
		return m_instance.get();
	}

}


