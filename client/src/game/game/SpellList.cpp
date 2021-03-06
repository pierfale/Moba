/*
 * SpellList.cpp
 *
 *  Created on: 27 mai 2013
 *      Author: pierre
 */

#include "SpellList.hpp"

namespace game {

	boost::shared_ptr<SpellList> SpellList::m_instance;

	SpellList::SpellList() {

	}

	void SpellList::add(Spell* spell) {
		for(unsigned int i=0; i<getInstance()->m_spells.size(); i++) {
			if(getInstance()->m_spells.at(i).getId() == spell->getId())
				return;
		}
		std::cout << spell->getName() << " ADDED" << std::endl;
		getInstance()->m_spells.push_back(spell);


	}
	Spell* SpellList::get(int i) {
		return &getInstance()->m_spells.at(i);
	}

	void SpellList::clear() {
		while(getInstance()->m_spells.size() > 0)
			getInstance()->m_spells.release(getInstance()->m_spells.begin()).release();
	}
	int SpellList::size() {
		return getInstance()->m_spells.size();
	}

	SpellList* SpellList::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new SpellList());
		return m_instance.get();
	}

}


