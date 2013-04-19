/*
 * client.h
 *
 *  Created on: 17 avr. 2013
 *      Author: Carl
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#define BUFFER_SIZE 128

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <network/iomanager.h>
#include <network/message.h>
#include "network/basic.h"

class client {
public:
	client(std::string addr, unsigned int port_num);
	virtual ~client();

	void connect(std::string addr, unsigned short port_num);

private:
	void handle_connect(const boost::system::error_code& error);
	void read();
	void handle_read(const boost::system::error_code& error);
	void client::write(const network::message& msg);
	void handle_write(const boost::system::error_code& error);

	network::io_manager _io_manager;
	network::message	_message_read;
	network::message	_message_written;

	boost::asio::io_service 		_io_service;
	boost::asio::ip::tcp::socket 	_socket;
	boost::array<char, BUFFER_SIZE> _network_buffer;

};

#endif /* CLIENT_H_ */
