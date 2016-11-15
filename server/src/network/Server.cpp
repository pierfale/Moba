/*
 * Server.cpp
 *
 *  Created on: 20 avr. 2013
 *      Author: pierre
 */

#include "Server.hpp"


namespace network {

	boost::shared_ptr<Server> Server::m_instance;

	Server::Server() : m_acceptor(NULL) {

	}

	void Server::init(int port) {
		log_out	"Launch server on port "+util::Cast::intToString(port) end_log_out;
		getInstance()->m_acceptor = new boost::asio::ip::tcp::acceptor(getInstance()->m_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
		getInstance()->accept();
	}

	void Server::run() {
		getInstance()->m_ios.run();
	}

	void Server::accept() {
		TcpSocket* sck = new TcpSocket(&m_ios);
		m_acceptor->async_accept(*sck->getSocket(), boost::bind(&Server::accept_handle, this, sck, boost::asio::placeholders::error));
	}

	void Server::accept_handle(TcpSocket* socket, const boost::system::error_code& error) {
		if(!error) {
			//need delete client
			Client* client = new Client(socket);
			m_clients.push_back(client);
			boost::thread(boost::bind(&Client::run, client));
			log_out "client connected : "+util::Cast::intToString(m_clients.size()) end_log_out;
		}
		else
			log_err error.message() end_log_err;
		accept();

	}

	void Server::sendAll(Packet packet) {
		for(boost::ptr_vector<Client>::iterator it = getInstance()->m_clients.begin(); it != getInstance()->m_clients.end(); ++it) {
			it->send(packet);
		}
	}

	void Server::removeClient(Client* client) {
		for(boost::ptr_vector<Client>::iterator it = getInstance()->m_clients.begin(); it != getInstance()->m_clients.end(); ++it) {
			if(&(*it) == client) {
				getInstance()->m_clients.release(it).release();
				log_out "client connected : "+util::Cast::intToString(getInstance()->m_clients.size()) end_log_out;
				return;
			}
		}
	}

	Client* Server::getClientByID(int id) {
		for(boost::ptr_vector<Client>::iterator it = getInstance()->m_clients.begin(); it != getInstance()->m_clients.end(); ++it) {
			if(it->getAccountID() == id)
				return &(*it);
		}
		return NULL;
	}

	Server* Server::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new Server());
		return m_instance.get();
	}

}


