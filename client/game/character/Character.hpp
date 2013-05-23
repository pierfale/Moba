/*
 * Character.hpp
 *
 *  Created on: 11 avr. 2013
 *      Author: pierre
 */

#ifndef GAME_CHARACTER_HPP_
#define GAME_CHARACTER_HPP_

#include <string>
#include "CharacterStat.hpp"
#include "../../util/Util.hpp"
#include "PacketType.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace game {

	class Character {

	public:
		Character(int id, std::string name);
		virtual ~Character();

		int getID();
		std::string getName();
		util::CoordFloat getCoord();
		util::CoordFloat getCoordExtra();
		network::PacketType::PacketContents getDirection();
		network::PacketType::PacketContents getFaction();
		CharacterStat* getStat();

		//setters
		void setCoord(util::CoordFloat coord);
		void setCoordExtra(util::CoordFloat coord);
		void setDirection(network::PacketType::PacketContents dir);
		void setFaction(network::PacketType::PacketContents faction);

	protected:
		static const float m_extraCoordNb;

		int m_id;
		std::string m_name;
		util::CoordFloat m_coord;
		util::CoordFloat m_coordExtra;
		network::PacketType::PacketContents m_direction;
		network::PacketType::PacketContents m_faction;
		CharacterStat* m_stat;
	};
}


#endif /* CHARACTER_HPP_ */
