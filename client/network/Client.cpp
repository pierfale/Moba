/*
 * Client.cpp
 *
 *  Created on: 9 avr. 2013
 *      Author: Carl
 */

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/foreach.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "Client.h"

using boost::asio::ip::tcp;

namespace network {

Client::Client(){
}

Client::~Client() {
	BOOST_FOREACH(tcp::socket& sock, connections){
		sock.close();
		std::cout << "connection closed" << std::endl;
	}
}

boost::shared_ptr<tcp::socket> Client::connect(boost::asio::ip::tcp::endpoint& ep, boost::system::error_code& ec){
	boost::asio::io_service io_service;
	boost::shared_ptr<tcp::socket> sock(new tcp::socket(io_service));

	sock.get()->connect(ep, ec);

	if(!ec)
		connections.push_back(sock.get());
	// else no connection established

	return sock;
}

boost::shared_ptr<tcp::socket> Client::connect(boost::asio::ip::address addr, unsigned short port_num, boost::system::error_code ec){
	tcp::endpoint ep(addr, port_num);
	return connect(ep, ec);
}

boost::shared_ptr<tcp::socket> Client::connect(std::string addr, unsigned short port_num, boost::system::error_code ec){
	tcp::endpoint ep(boost::asio::ip::address::from_string(addr), port_num);
	return connect(ep, ec);
}

} /* namespace network */
