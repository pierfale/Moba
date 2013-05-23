/*
 * Message_game.cpp
 *
 *  Created on: 22 avr. 2013
 *      Author: pierre
 */

#include "Message_game.hpp"
#include "../Network.hpp"

namespace network {

	void Message_game::process(Packet packet) {
		if(packet.getType() == PacketType::GAME_ANSWERREADY) {
			game::GamePlayerList::removeByID(game::CurrentCharacter::get()->getID());
			graphics::Graphics::getWindow()->setContentPane(new graphics::Gameboard());
		}
		else if(packet.getType() == PacketType::GAME_ANSWERMOVE) {
			float x, y;
			packet >> &x >> &y;
			if(game::CurrentCharacter::get()->getCoord() == util::CoordFloat(0,0)) {
				game::CurrentCharacter::get()->setCoord(util::CoordFloat(x,y));
			}
			else
				game::CurrentCharacter::get()->setCoordExtra(util::CoordFloat(x,y));
		}
		else if (packet.getType() == PacketType::GAME_PLAYERMOVE) {
			int id, dir;
			float x, y;
			packet >> &id >> &x >> &y >> &dir;
			game::Player* p = NULL;
			if(id == game::CurrentCharacter::get()->getID())
				p = game::CurrentCharacter::get();
			else
				p = game::GamePlayerList::getByID(id);
			if(p != NULL) {
				p->setCoordExtra(util::CoordFloat(p->getCoord().x-x, p->getCoord().y-y));
				p->setDirection(static_cast<PacketType::PacketContents>(dir));
			}
		}
		else if (packet.getType() == PacketType::GAME_PLAYERTELEPORT) {
			int id, dir;
			float x, y;
			packet >> &id >> &x >> &y >> &dir;
			game::Player* p = NULL;
			if(id == game::CurrentCharacter::get()->getID())
				p = game::CurrentCharacter::get();
			else
				p = game::GamePlayerList::getByID(id);
			if(p != NULL) {
				p->setCoord(util::CoordFloat(x, y));
				p->setDirection(static_cast<PacketType::PacketContents>(dir));
			}
		}
		else if(packet.getType() == PacketType::GAME_STAT_ALL) {
			std::cout << "All Stat !!! " << std::endl;
			int id;
			int life;
			int maxLife;
			int mana;
			int maxMana;
			float attackSpeed;
			float movementSpeed;
			int physicalAttack;
			int magicalAttack;
			int physicalArmor;
			int magicalArmor;
			float range;

			packet >> &id >> &life >> &maxLife >> &mana >> &maxMana >> &attackSpeed >> &movementSpeed >> &physicalAttack >> &magicalAttack >> &physicalArmor >> &magicalArmor >> &range;
			game::Player* p = NULL;
			if(id == game::CurrentCharacter::get()->getID())
				p = game::CurrentCharacter::get();
			else
				p = game::GamePlayerList::getByID(id);
			if(p != NULL) {
				p->getStat()->setLife(life);
				p->getStat()->setMaxLife(maxLife);
				p->getStat()->setMana(mana);
				p->getStat()->setMaxMana(maxMana);
				p->getStat()->setAttackSpeed(attackSpeed);
				p->getStat()->setMovementSpeed(movementSpeed);
				p->getStat()->setPhysicalAttack(physicalAttack);
				p->getStat()->setMagicalAttack(magicalAttack);
				p->getStat()->setPhysicalArmor(physicalArmor);
				p->getStat()->setMagicalArmor(magicalArmor);
				p->getStat()->setRange(range);
			}
		}
		else if((packet.getType() & 0xFFFF0000) == PacketType::GAME_STAT) {
			int id, value;
			packet >> &id >> &value;
			game::Player* p = NULL;
			if(id == game::CurrentCharacter::get()->getID())
				p = game::CurrentCharacter::get();
			else
				p = game::GamePlayerList::getByID(id);
			if(p != NULL) {
				if(packet.getType() == PacketType::GAME_STAT_LIFE)
					p->getStat()->setLife(value);
			}
		}
		else if(packet.getType() == PacketType::GAME_PLAYERLAUNCHSINGLETARGETSPELL) {
			int id, casterID, targetID;
			packet >> &id >> &casterID >> &targetID;
			game::Player* caster = NULL;
			if(casterID == game::CurrentCharacter::get()->getID())
				caster = game::CurrentCharacter::get();
			else
				caster = game::GamePlayerList::getByID(casterID);

			game::Player* target = NULL;
			if(targetID == game::CurrentCharacter::get()->getID())
				target = game::CurrentCharacter::get();
			else
				target = game::GamePlayerList::getByID(targetID);

			if(caster != NULL && target != NULL)
				graphics::Gameboard::addAnimation(new graphics::AutoAttackAnim(caster, target));
		}
		else if(packet.getType() == PacketType::GAME_ANSWERTARGET) {
			int id;
			packet >> &id;
			if(id == 0) {
				game::CurrentCharacter::setTarget(NULL);
			}
			else {
				game::Player* p = game::GamePlayerList::getByID(id);
				if(p != NULL)
					game::CurrentCharacter::setTarget(p);
			}
		}
	}
}


