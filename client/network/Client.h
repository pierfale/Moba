/*
 * Client.h
 *
 *  Created on: 9 avr. 2013
 *      Author: Carl
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace network {

class Client {
public:
	static boost::shared_ptr<boost::asio::ip::tcp::socket> connect(boost::asio::ip::tcp::endpoint& ep, boost::system::error_code& ec);
	static boost::shared_ptr<boost::asio::ip::tcp::socket> connect(boost::asio::ip::address addr, unsigned short port_num, boost::system::error_code& ec);
	static boost::shared_ptr<boost::asio::ip::tcp::socket> connect(std::string addr, unsigned short port_num, boost::system::error_code& ec);

	virtual ~Client();

private:
	Client();
};

} /* namespace network */
#endif /* CLIENT_H_ */
