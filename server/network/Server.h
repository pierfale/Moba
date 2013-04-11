/*
 * Server.h
 *
 *  Created on: 11 avr. 2013
 *      Author: Carl
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <boost/asio.hpp>

namespace network {

class Server {
public:
	Server(boost::asio::io_service& io_service, int port);
	virtual ~Server();

private:
	void startAccept();
	void handleAccept(boost::shared_ptr<ConnectionHandler> newConnection, const boost::system::error_code& error);

	boost::asio::ip::tcp::acceptor acceptor;
};

} /* namespace network */

#endif /* SERVER_H_ */
