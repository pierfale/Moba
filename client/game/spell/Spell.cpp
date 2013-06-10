/*
 * Spell.cpp
 *
 *  Created on: 22 avr. 2013
 *      Author: Béni
 */

#include "Spell.hpp"
#include "../../network/Network.hpp"

namespace game {

	Spell::Spell(int id, std::string name, std::string describe, std::string image, sf::IntRect subrect) : m_subrect(subrect) {
		m_id = id;
		m_name = name;
		m_describe = describe;
		m_image = image;
	}

	int Spell::getId() {
		return m_id;
	}

	std::string Spell::getImage() {
		return m_image;
	}

	std::string Spell::getName() {
		return m_name;
	}

	std::string Spell::getContents() {
		return m_describe;
	}

	sf::IntRect Spell::getSubrect() {
		return m_subrect;
	}

	void Spell::send() {
		if(game::CurrentCharacter::getTarget() != NULL) {
			network::Packet packet(network::Network::getSocket(), network::PacketType::GAME_ASKLAUNCHSINGLETARGETSPELL);
			packet << m_id << game::CurrentCharacter::getTarget()->getID();
			packet.send();
		}
	}
}
