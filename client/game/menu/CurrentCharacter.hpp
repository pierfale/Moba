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
#include "../../graphics/game/character/UserPlayer.hpp"
#include "../../network/Network.hpp"
#include "Packet.hpp"

namespace game {

	class CurrentCharacter {

	public:
		static Player* get();
		static graphics::UserPlayer* getView();
		static Character* getTarget();
		static void set(Player* player);
		static void set(graphics::UserPlayer* player);
		static void setTarget(Character* player);
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
		graphics::UserPlayer* m_currentView;
		Character* m_target;
		std::vector<util::CoordInt> m_path;
	};
}


#endif /* CURRENTCHARACTER_HPP_ */
