/*
 * Message_game.cpp
 *
 *  Created on: 28 avr. 2013
 *      Author: pierre
 */

#include "Message_game.hpp"


namespace network {

	void Message_game::process(Packet packet, Client* client) {

		if(packet.getType() == PacketType::GAME_ASKREADY) {
			client->setReady(true);
			client->getGame()->checkPlayerReady();
		}
		if(packet.getType() == PacketType::GAME_ASKMOVE) {
			int size;
			packet >> &size;
			client->getCharacter()->clearGoal();
			client->getCharacter()->setState(PLAYER_STATE_MOVETO);
			for(int i=0; i<size; i++) {
				int x, y;
				packet >> &x >> &y;
				client->getCharacter()->addGoal(util::CoordInt(x, y));
			}
		}
		if(packet.getType() == PacketType::GAME_ASKTARGET) {
			int id;
			packet >> &id;
			if(id != 0) {
				Client* p = client->getGame()->getPlayerByID(id);
				if(p != NULL) {
					client->getCharacter()->setTarget(p->getCharacter());
					client->getCharacter()->setState(PLAYER_STATE_TARGET);
				}
			}
			else {
				client->getCharacter()->setTarget(NULL);
				client->getCharacter()->setState(PLAYER_STATE_NONE);
			}
		}
		if(packet.getType() == PacketType::GAME_ASKLAUNCHSINGLETARGETSPELL) {
			int idSpell, idPlayer;
			packet >> &idSpell >> &idPlayer;
			Client* p = client->getGame()->getPlayerByID(idPlayer);
			if(p != NULL) {
				if(SingleTargetSpell::process(idSpell, client->getCharacter(), p->getCharacter())) {
					Packet answer(NULL, PacketType::GAME_PLAYERLAUNCHSINGLETARGETSPELL);
					answer << idSpell << client->getCharacter()->getID() << idPlayer;
					client->getGame()->sendAll(answer);
				}
			}
		}
	}

}



