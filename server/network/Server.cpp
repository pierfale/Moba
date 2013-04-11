/*
 * Server.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: Carl
 */

#include "Server.h"

using boost::asio::ip::tcp;

namespace network {

Server::Server(boost::asio::io_service& io_service, int port)
: acceptor(io_service, tcp::endpoint(tcp::v4(), port)){
	startAccept();
}

Server::~Server() {
	// TODO Auto-generated destructor stub
}

void Server::startAccept(){
	ConnectionHandler newConnection = ConnectionHandler::create(acceptor.get_io_service());;

	acceptor.async_accept(newConnection.socket(),
			boost::bind(&Server::handleAccept, this, newConnection,
					boost::asio::placeholders::error));
}

void Server::handleAccept(boost::shared_ptr<ConnectionHandler> newConnection, const boost::system::error_code& error){
	if (!error)
	{
		std::cout << "connection received" << std::endl;
		newConnection->start();
		startAccept();
	}
}

} /* namespace network */
