/*
 * basic.cpp
 *
 *  Created on: 16 avr. 2013
 *      Author: Carl
 */

#include "basic.h"

namespace network {

basic::basic(){}
basic::~basic() {}

boost::shared_ptr<boost::asio::ip::tcp::socket> basic::connect(boost::asio::io_service& ios, boost::asio::ip::tcp::endpoint& ep, boost::system::error_code& ec){
	boost::shared_ptr<boost::asio::ip::tcp::socket> sock(new boost::asio::ip::tcp::socket(ios));
	sock->connect(ep, ec);

	return sock;
}

boost::shared_ptr<boost::asio::ip::tcp::socket> basic::connect(boost::asio::io_service& ios, boost::asio::ip::address addr, unsigned short port_num, boost::system::error_code& ec){
	boost::asio::ip::tcp::endpoint ep(addr, port_num);
	return connect(ios, ep, ec);
}

boost::shared_ptr<boost::asio::ip::tcp::socket> basic::connect(boost::asio::io_service& ios, std::string addr, unsigned short port_num, boost::system::error_code& ec){
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(addr), port_num);

	return connect(ios, ep, ec);
}

} /* namespace network */
