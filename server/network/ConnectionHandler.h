/*
 * ConnectionHandler.h
 *
 *  Created on: 11 avr. 2013
 *      Author: Carl
 */

#ifndef CONNECTIONHANDLER_H_
#define CONNECTIONHANDLER_H_

namespace network {

class ConnectionHandler : public boost::enable_shared_from_this<ConnectionHandler> {
public:
	static boost::shared_ptr<ConnectionHandler> create(boost::asio::io_service& ios);
	boost::asio::ip::tcp::socket& socket();

	void start();

private:
	ConnectionHandler(boost::asio::io_service& io_service);

	void handle_write(const boost::system::error_code& error);

	boost::asio::ip::tcp::socket m_socket;
	std::string m_message;
};

} /* namespace network */

#endif /* CONNECTIONHANDLER_H_ */
