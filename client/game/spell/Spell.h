/*
 * Spell.h
 *
 *  Created on: 22 avr. 2013
 *      Author: Béni
 */

#ifndef SPELL_H_
#define SPELL_H_

namespace game {

class Player;

	class Spell {

	public:
		Spell();
		Spell(Player* player);
		virtual ~Spell();

		void callSpell(int id, Player* target);
		void autoAttack(Player* target);

		bool getCast();
		bool onRange(Player* target);
		void setCast(bool cast);

	private:
		bool m_cast;
		int m_range;
		Player* m_player;
	};

} /* namespace game */
#endif /* SPELL_H_ */
