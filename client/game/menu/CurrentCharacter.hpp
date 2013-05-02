/*
 * CurrentCharacter.hpp
 *
 *  Created on: 23 avr. 2013
 *      Author: pierre
 */

#ifndef CURRENTCHARACTER_HPP_
#define CURRENTCHARACTER_HPP_

#include <boost/shared_ptr.hpp>
#include "../character/Player.hpp"
#include "../../network/Network.hpp"
#include "Packet.hpp"

namespace game {

	class CurrentCharacter {

	public:
		static Player* get();
		static void set(Player* player);
		static void setPath(std::vector<util::CoordInt> path);
		static util::CoordInt getNextDest();
		static void destReached();
		static bool isLastDest();
		static void reset();

	private:
		CurrentCharacter();
		static CurrentCharacter* getInstance();
		static boost::shared_ptr<CurrentCharacter> m_instance;
		Player* m_current;
		std::vector<util::CoordInt> m_path;
	};
}


#endif /* CURRENTCHARACTER_HPP_ */
