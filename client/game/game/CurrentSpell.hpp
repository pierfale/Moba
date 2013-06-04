/*
 * CurrentSpell.hpp
 *
 *  Created on: 30 mai 2013
 *      Author: pierre
 */

#ifndef CURRENTSPELL_HPP_
#define CURRENTSPELL_HPP_

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "../spell/Spell.hpp"

namespace game {

	class CurrentSpell {

	public:
		static void set(Spell* spell);
		static Spell* get();

	private:
		CurrentSpell();
		static CurrentSpell* getInstance();
		static boost::shared_ptr<CurrentSpell> m_instance;
		Spell* m_spell;

	};
}


#endif /* CURRENTSPELL_HPP_ */
