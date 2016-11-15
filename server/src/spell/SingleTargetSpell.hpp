/*
 * SingleTargetSpell.hpp
 *
 *  Created on: 4 mai 2013
 *      Author: pierre
 */

#ifndef SINGLETARGETSPELL_HPP_
#define SINGLETARGETSPELL_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <map>

#include "../client/Player.hpp"
#include "../log/Log.hpp"
#include "../util/Util.hpp"

class SingleTargetSpell {

public:
	static bool process(int idSpell, Player* caster, Player* target);

	//	1
	bool autoAttack(Player* caster, Player* target);
	//PowerFul Strike
	bool spell10(Player* caster, Player* target);
	//FireBall
	bool spell11(Player* caster, Player* target);

	bool launchSpell(Player* caster, Player* target, int id, float range, float cooldowns, bool isPhysical, int damage);

private:
	SingleTargetSpell();
	static SingleTargetSpell* getInstance();
	static boost::shared_ptr<SingleTargetSpell> m_instance;
	std::map<int, boost::function<bool(Player*, Player*)> > m_spells;
};


#endif /* SINGLETARGETSPELL_HPP_ */
