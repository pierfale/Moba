/*
 * ConnectionHandler.cpp
 *
 *  Created on: 11 avr. 2013
 *      Author: Carl
 */

#include <boost/asio.hpp>
#include "ConnectionHandler.h"

using boost::asio::ip::tcp;

namespace network {

ConnectionHandler::ConnectionHandler(boost::asio::io_service& io_service)
: m_socket(io_service)
{}


ConnectionHandler::~ConnectionHandler() {
	// TODO Auto-generated destructor stub
}

tcp::socket& ConnectionHandler::socket(){
	return m_socket;
}

boost::shared_ptr<ConnectionHandler> create(boost::asio::io_service& ios){
	return boost::shared_ptr<ConnectionHandler>(new ConnectionHandler(ios));
}


void ConnectionHandler::start(){
	m_message = "Bienvenue sur le serveur!";

	boost::asio::async_write(m_socket, boost::asio::buffer(m_message),
			boost::bind(&ConnectionHandler::handle_write, this,
					boost::asio::placeholders::error)
	);
}

void ConnectionHandler::handle_write(const boost::system::error_code& error){
	if (!error){
		// Autres actions éventuelles
	}
}

} /* namespace network */
