/*
 * Client.hpp
 *
 *  Created on: 21 avr. 2013
 *      Author: pierre
 */

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "../network/TcpSocket.hpp"
#include "Packet.hpp"
#include "Player.hpp"
#include "../log/Log.hpp"
#include "../util/Util.hpp"

class GameCreate;
class Game;
class Chat;

class Client {

public:
	Client(network::TcpSocket* socket);
	~Client();
	void close();
	void run();
	void stop();
	void send(network::Packet packet);
	boost::asio::ip::tcp::socket* getSocket();
	void setAccount(int id, std::string pseudo);
	int getAccountID();
	void setCharacter(Player* player);
	Player* getCharacter();
	std::string getPseudo();
	GameCreate* getGameCreate();
	void setGameCreate(GameCreate* game);
	Game* getGame();
	void setGame(Game* game);

	void setReady(bool state);
	bool isReady();

private:
	void close_handle();
	network::TcpSocket* m_socket;
	bool m_run;
	bool m_close;
	bool m_ready;

	int m_accountID;
	std::string m_pseudo;
	Player* m_character;

	GameCreate* m_currGameCreate;
	Game* m_currGame;
};


#endif /* CLIENT_HPP_ */
