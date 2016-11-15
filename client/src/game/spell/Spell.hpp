/*
 * Spell.h
 *
 *  Created on: 22 avr. 2013
 *      Author: Béni
 */

#ifndef SPELL_H_
#define SPELL_H_

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../../util/Util.hpp"
#include "Packet.hpp"
#include "PacketType.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace game {

	class Spell {

	public:
		Spell(int id, std::string name, std::string describe, std::string image, sf::IntRect subrect);
		int getId();
		std::string getImage();
		std::string getName();
		std::string getContents();
		sf::IntRect getSubrect();
		void send();
	private:
		int m_id;
		std::string m_name;
		std::string m_describe;
		std::string m_image;
		sf::IntRect m_subrect;
	};

} /* namespace game */
#endif /* SPELL_H_ */
