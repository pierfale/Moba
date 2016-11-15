/*
 * Pvp.cpp
 *
 *  Created on: 28 avr. 2013
 *      Author: pierre
 */

#include "Pvp.hpp"
#include "../Game.hpp"

util::CoordFloat Pvp::m_team1Spawn = util::CoordFloat(100, 100);
util::CoordFloat Pvp::m_team2Spawn = util::CoordFloat(100, 400);

Pvp::Pvp() : m_scoreTeam1(0) , m_scoreTeam2(0), m_id(0), m_expTeam1(0), m_expTeam2(0) ,m_time(150.0) {
	m_map = "ressources/game/Battleground";
}

void Pvp::randomizeCoord() {
	srand (time(NULL));
	int tmp;
	tmp = rand() % 2;
	m_team1Spawn.x = 100 + 300 * tmp;
	tmp = rand() % 2;
	m_team1Spawn.y = 100 + 300 * tmp;
	tmp = rand() % 2;
	m_team2Spawn.x = 1100 + 300 * tmp;
	tmp = rand() % 2;
	m_team2Spawn.y = 1100 + 300 * tmp;
}

void Pvp::init() {
	for(std::map<Player*, Client*>::iterator it = m_game->getClientMap()->begin(); it != m_game->getClientMap()->end(); ++it) {
		randomizeCoord();
		if(it->first->getTeam() == network::PacketType::FACTION_TEAM1)
			it->first->setCoord(m_team1Spawn);
		else
			it->first->setCoord(m_team2Spawn);
	}
	network::Packet packet(NULL, network::PacketType::GAME_MODE);
	packet << m_id;
	m_game->sendAll(packet);

}

void Pvp::start() {
	m_timer.restart();
}

bool Pvp::run() {
	if (m_timer.elapsed() > m_time) {
		end();
		return false;
	}
	return true;
}

void Pvp::expManage() {

	if (m_scoreTeam1 > m_scoreTeam2) {
		m_expTeam1 = m_game->getClientMap()->size() + 5;
		m_expTeam2 = m_game->getClientMap()->size() + 2;
	} else {
		m_expTeam1 = m_game->getClientMap()->size() + 2;
		m_expTeam2 = m_game->getClientMap()->size() + 5;
	}

	for(std::map<Player*, Client*>::iterator it = m_game->getClientMap()->begin(); it != m_game->getClientMap()->end(); ++it) {

		if (it->first->getTeam() == network::PacketType::FACTION_TEAM1)
			it->first->incExp(m_expTeam1);
		else
			it->first->incExp(m_expTeam2);

		Database::update("UPDATE characters SET Characters_Exp ='"+
				util::Cast::intToString(it->first->getExp())+
				"' WHERE Characters_ID ='"+util::Cast::intToString(it->first->getID())+"'");
	}
}

void Pvp::end() {
	expManage();
	network::Packet packet(NULL, network::PacketType::GAME_END);
	packet << m_expTeam1 << m_expTeam2;
	m_game->sendAll(packet);
}


void Pvp::dead(Client* client, Player* killer) {
	randomizeCoord();
	if(client->getCharacter()->getTeam() == network::PacketType::FACTION_TEAM1) {
		m_scoreTeam2++;
		client->getCharacter()->setCoord(m_team1Spawn);
	} else {
		m_scoreTeam1++;
		client->getCharacter()->setCoord(m_team2Spawn);
	}

	network::Packet packetscore(NULL, network::PacketType::GAME_SCORE_UPGRADE);
	packetscore << m_scoreTeam1 << m_scoreTeam2 << client->getCharacter()->getID() << killer->getID();
	m_game->sendAll(packetscore);

	network::Packet packet(NULL, network::PacketType::GAME_PLAYERTELEPORT);
	packet << client->getCharacter()->getID() << client->getCharacter()->getCoord().x << client->getCharacter()->getCoord().y << network::PacketType::DIRECTION_NONE;
	m_game->sendAll(packet);
	client->getCharacter()->setAlive(true);

	client->getCharacter()->setTarget(NULL);
	client->getCharacter()->getStat()->setLife(client->getCharacter()->getStat()->maxLife());
	network::Packet packet2(NULL, network::PacketType::GAME_STAT_LIFE);
	packet2 << client->getCharacter()->getID() << client->getCharacter()->getStat()->life();
	m_game->sendAll(packet2);

	m_game->getChat()->send(killer->getName()+" have slained "+client->getCharacter()->getName()+" !");
}

