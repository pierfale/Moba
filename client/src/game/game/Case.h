/*
 * Case.h
 *
 *  Created on: 8 avr. 2013
 *      Author: Béni
 */

#ifndef CASE_H_
#define CASE_H_

namespace game {

class Case {
	public:
		Case();
		Case(int id);
		virtual ~Case();

		int getId();
		void setPassable(bool passable);
		bool getPassable();

	private:
		bool m_passable;
		int m_id;
};

} /* namespace game */
#endif /* CASE_H_ */
