/*
 * CurrentSpell.cpp
 *
 *  Created on: 30 mai 2013
 *      Author: pierre
 */

#include "CurrentSpell.hpp"

namespace game {

	boost::shared_ptr<CurrentSpell> CurrentSpell::m_instance;

	CurrentSpell::CurrentSpell() {
		m_spell = NULL;
	}

	void CurrentSpell::set(Spell* spell) {
		getInstance()->m_spell = spell;


	}
	Spell* CurrentSpell::get() {
		return getInstance()->m_spell;
	}

	CurrentSpell* CurrentSpell::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new CurrentSpell());
		return m_instance.get();
	}

}



