/*
 * Client.cpp
 *
 *  Created on: 21 avr. 2013
 *      Author: pierre
 */

#include "Client.hpp"
#include "../message/Message_session.hpp"
#include "../message/Message_game.hpp"
#include "../message/Message_chat.hpp"
#include "../game/GameCreate.hpp"
#include "../game/Game.hpp"
#include "../chat/Chat.hpp"


	Client::Client(network::TcpSocket* socket) : m_socket(socket), m_accountID(0), m_character(NULL) {
		log_out "new client !" end_log_out;
		m_run = true;
		m_close = false;
		m_currGameCreate = NULL;
		m_currGame = NULL;
		m_ready = false;
	}

	Client::~Client() {
		delete m_socket;
		if(m_character != NULL)
			delete m_character;
	}

	void Client::close() {
		m_close = true;
		m_socket->getSocket()->close();
	}

	void Client::stop() {
		m_run = false;
	}

	void Client::send(network::Packet packet) {
		packet.setSocket(m_socket->getSocket());
		packet.send();
	}

	void Client::setAccount(int id, std::string pseudo) {
		m_accountID = id;
		m_pseudo = pseudo;
	}

	int Client::getAccountID() {
		return m_accountID;
	}

	std::string Client::getPseudo() {
		return m_pseudo;
	}

	 void Client::setCharacter(Player* player) {
		if(m_character != NULL)
			delete m_character;
		m_character = player;
	}

	Player* Client::getCharacter() {
		return m_character;
	}

	GameCreate* Client::getGameCreate() {
		return m_currGameCreate;
	}

	void Client::setGameCreate(GameCreate* game) {
		m_currGameCreate = game;
		if(game != NULL)
			game->addPlayer(this);
	}

	Game* Client::getGame() {
		return m_currGame;
	}

	void Client::setGame(Game* game) {
		m_currGame = game;
	}

	void Client::setReady(bool state) {
		m_ready = state;
	}

	bool Client::isReady() {
		return m_ready;
	}

	void Client::run() {
		while(m_run) {

			network::Packet packet(m_socket->getSocket(), network::PacketType::UNDEFINED);
			if(!packet.receive()) {
				close_handle();
				return;
			}
			log_out "packet receive! type="+util::Cast::intToHexString(packet.getType()) end_log_out;
			int typeFirstMask = 0xFF000000;
			if((packet.getType() & typeFirstMask) == network::PacketType::SESSION) {
				network::Message_session::process(packet, this);
			}
			else if((packet.getType() & typeFirstMask) == network::PacketType::GAME) {
				network::Message_game::process(packet, this);
			}
			else if((packet.getType() & typeFirstMask) == network::PacketType::CHAT) {
				network::Message_chat::process(packet, this);
			}
			else
				log_err "unknown packet first type : "+util::Cast::intToHexString((packet.getType() & typeFirstMask)) end_log_err;
		}
		while(!m_close) {
			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
			log_out "wait" end_log_out;
		}
		close_handle();
	}

	void Client::close_handle() {
		//createGame
		if(m_currGameCreate != NULL) {
			if(m_currGameCreate->removePlayer(this)) {
				network::Packet answer(getSocket(), network::PacketType::SESSION_GAMEDELETE);
				answer << m_currGameCreate->getID();
				//TODO create list
				network::Server::sendAll(answer);
				GameCreateList::remove(m_currGameCreate);
				delete m_currGameCreate;
			}
			else {
				network::Packet answer(getSocket(), network::PacketType::SESSION_PLAYERQUITGAME);
				answer << m_character->getID();
				m_currGameCreate->sendAll(answer);
			}
		}
		//Game
		if(m_currGame != NULL) {
			m_currGame->setClient(m_character->getID(), NULL);
		}
		network::Server::removeClient(this);
		log_out "client closed !" end_log_out;
		delete this;
	}

	boost::asio::ip::tcp::socket* Client::getSocket() {
		return m_socket->getSocket();
	}

