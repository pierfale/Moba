/*
 * SpellReader.hpp
 *
 *  Created on: 27 mai 2013
 *      Author: pierre
 */

#ifndef SPELLREADER_HPP_
#define SPELLREADER_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "Spell.hpp"
#include "../../util/Util.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace game {

	class SpellReader {

	public:
		SpellReader();
		bool load(std::string path);
		static Spell* get(int id);
		static std::vector<int> keySet();


	private:
		Spell* evalLine(std::string line);
		bool isblank(char c);
		static SpellReader* getInstance();
		static boost::shared_ptr<SpellReader> m_instance;
		boost::ptr_vector<Spell> m_spells;
	};
}



#endif /* SPELLREADER_HPP_ */
