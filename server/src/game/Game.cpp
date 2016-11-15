/*
 * Game.cpp
 *
 *  Created on: 28 avr. 2013
 *      Author: pierre
 */

#include "Game.hpp"
#include "GameList.hpp"

Game::Game(GameMode* mode) {
	m_id = GameCreateList::getNextID();
	m_mode = mode;
	m_mode->setGame(this);
	m_chat = new Chat(network::PacketType::CHAT_GAME);
}

Game::Game(GameMode* mode, GameCreate* game) {
	m_id = game->getID();
	m_mode = mode;
	m_mode->setGame(this);
	m_chat = game->getChat();
	for(int i=0; i<game->playerSize(); i++) {
		game->getPlayer(i)->setReady(false);
		game->getPlayer(i)->setGameCreate(NULL);
		game->getPlayer(i)->setGame(this);
		m_clients.insert(std::pair<Player*, Client*>(game->getPlayer(i)->getCharacter(), game->getPlayer(i)));
	}
	GameCreateList::remove(game);
	delete game;
	log_out "New Game : ID="+util::Cast::intToString(m_id)+", player="+util::Cast::intToString(m_clients.size()) end_log_out;
}

int Game::getID() {
	return m_id;
}

int Game::playerSize() {
	return m_clients.size();
}

std::map<Player*, Client*>* Game::getClientMap() {
	return &m_clients;
}

void Game::setClient(int id, Client* client) {
	std::cout << "ENTER SET" << std::endl;
	for(std::map<Player*, Client*>::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
		if(it->first->getID() == id) {
			std::cout << "1" << std::endl;
			if(client == NULL) {
				std::cout << "2" << std::endl;
				m_chat->removeClient(it->second);
				std::cout << "3" << std::endl;
				m_chat->send(it->first->getName()+" disconnected");
				std::cout << "4" << std::endl;
			}
			else
				m_chat->send(it->first->getName()+" reconnected");
			m_clients[it->first] = client;
			return;
		}
	}
	std::cout << "QUIT SET" << std::endl;
}

Client* Game::getPlayerByID(int id) {
	for(std::map<Player*, Client*>::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
		if(it->first->getID() == id)
			return it->second;
	}
	return NULL;

}

void Game::checkPlayerReady() {
	for(std::map<Player*, Client*>::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
		if(!it->second->isReady())
			return;
	}
	m_mode->init();

	for(std::map<Player*, Client*>::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
		it->first->updateStat();

		it->first->clearGoal();
		it->first->setTarget(NULL);
		it->first->setAlive(true);

		network::Packet answer(NULL, network::PacketType::GAME_PLAYERTELEPORT);
		answer << it->first->getID() << it->first->getCoord().x << it->first->getCoord().y;
		sendAll(answer);
		network::Packet answer2(NULL, network::PacketType::GAME_STAT_ALL);
		answer2 << it->first->getID();
		answer2 << it->first->getStat()->life();
		answer2 << it->first->getStat()->maxLife();
		answer2 << it->first->getStat()->mana();
		answer2 << it->first->getStat()->maxMana();
		answer2 << it->first->getStat()->attackSpeed();
		answer2 << it->first->getStat()->movementSpeed();
		answer2 << it->first->getStat()->physicalAttack();
		answer2 << it->first->getStat()->magicalAttack();
		answer2 << it->first->getStat()->physicalArmor();
		answer2 << it->first->getStat()->magicalArmor();
		answer2 << it->first->getStat()->range();
		sendAll(answer2);

		network::Packet answer3(it->second->getSocket(), network::PacketType::GAME_ALLSPELL);
		answer3 << it->first->spellSize();
		for(int i=0; i<it->first->spellSize(); i++)
			answer3 << it->first->getSpell(i);
		answer3.send();
	}


	network::Packet answer2(NULL, network::PacketType::GAME_ANSWERREADY);
	answer2 << m_mode->getMap();
	sendAll(answer2);

	m_chat->set(network::PacketType::CHAT_GAME);

}

void Game::sendAll(network::Packet packet) {
	for(std::map<Player*, Client*>::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
		std::cout << "::" << &(*it->second) << ":" << it->second << std::endl;
		if(&(*it->second) != NULL)
			it->second->send(packet);
	}
}

void Game::sendAllOther(network::Packet packet, Client* client) {
	for(std::map<Player*, Client*>::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
		if(&(*it->second) != client && &(*it->second) != NULL)
			it->second->send(packet);
	}
}
void Game::run() {
	while(m_mode->run()) {
		for(std::map<Player*, Client*>::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
			it->first->checkAutoAttack();
			it->first->updateCoord();
		}
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	end();
}

void Game::end() {
	for(std::map<Player*, Client*>::iterator it = m_clients.begin(); it != m_clients.end(); ++it) {
		if(&(*it->second) != NULL) {
			it->first->clearGoal();
			it->first->setTarget(NULL);
			it->first->setAlive(true);
			it->second->setGame(NULL);
		}
	}

	GameList::remove(this);
	delete this;
}

GameMode* Game::getMode() {
	return m_mode;
}

Chat* Game::getChat() {
	return m_chat;
}
