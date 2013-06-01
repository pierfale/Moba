/*
 * SpellReader.cpp
 *
 *  Created on: 27 mai 2013
 *      Author: pierre
 */

#include "SpellReader.hpp"

namespace game {

	boost::shared_ptr<SpellReader> SpellReader::m_instance;

	SpellReader::SpellReader() {

	}

	bool SpellReader::load(std::string path) {
		std::ifstream file(path.c_str(), std::ios::in);
		if(!file) {
			log_err "Unable to open "+path end_log_err;
			return false;
		}
		std::string line;
		while(std::getline(file, line))  {
			Spell* spell = evalLine(line);
			if(spell != NULL) {
				getInstance()->m_spells.push_back(spell);
			}
		}

		file.close();
		return true;
	}

	Spell* SpellReader::evalLine(std::string line) {
		unsigned int cursor = 0;
		std::vector<std::string> args;
		for(int i=0; i<8; i++) {
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
		return new Spell(util::Cast::stringToInt(args.at(0)), args.at(1), args.at(2), args.at(3), sf::IntRect(util::Cast::stringToInt(args.at(4)), util::Cast::stringToInt(args.at(5)), util::Cast::stringToInt(args.at(6)), util::Cast::stringToInt(args.at(7))));

	}

	bool SpellReader::isblank(char c) {
		char blank [] = {' ', '\t'};
		for(int i=0; i<2; i++) {
			if(c == blank[i])
				return true;
		}
		return false;
	}

	Spell* SpellReader::get(int id) {
		for(boost::ptr_vector<Spell>::iterator it = getInstance()->m_spells.begin(); it != getInstance()->m_spells.end(); ++it) {
			if(it->getId() == id)
				return &(*it);
		}
		return NULL;
	}

	std::vector<int> SpellReader::keySet() {
		std::vector<int> v;
		for(boost::ptr_vector<Spell>::iterator it = getInstance()->m_spells.begin(); it != getInstance()->m_spells.end(); ++it) {
			v.push_back(it->getId());
		}
		return v;
	}

	SpellReader* SpellReader::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new SpellReader());
		return m_instance.get();
	}

}





