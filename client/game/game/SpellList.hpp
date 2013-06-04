/*
 * SpellList.hpp
 *
 *  Created on: 27 mai 2013
 *      Author: pierre
 */

#ifndef SPELLLIST_HPP_
#define SPELLLIST_HPP_

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "../spell/Spell.hpp"

namespace game {

	class SpellList {

	public:
		static void add(Spell* spell);
		static Spell* get(int i);
		static int size();
		static void clear();

	private:
		SpellList();
		static SpellList* getInstance();
		static boost::shared_ptr<SpellList> m_instance;
		boost::ptr_vector<Spell> m_spells;
	};
}


#endif /* SPELLLIST_HPP_ */
