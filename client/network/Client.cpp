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
	/* close all opened connections */
	BOOST_FOREACH(boost::asio::ip::tcp::socket& s, connections){
		s.close();
	}
}

/**
 * Connect to ep
 * @param ep endpoint which the client connect to
 * @param ec contains potential errors
 * @return a shared pointer to the socket created by the client
 */
boost::shared_ptr<tcp::socket> Client::connect(tcp::endpoint ep, boost::system::error_code ec){
	boost::asio::io_service io_service;

	/*
	 * ec should be null, so that we can know if an error occur
	 * during the call to connect() function
	 */
	if(ec)
		ec();

	boost::shared_ptr<tcp::socket> sock(new tcp::socket(io_service));
	(*sock).connect(ep, ec);

	/*
	 * add the socket to the connection's vector,
	 * thus, it can be closed easily when the Client
	 * is destroyed
	 */
	if(!ec){
		connections.push_back(sock.get());
	}

	return sock;
}

/**
 * Connect the client to addr on port port_num
 *
 * @param addr IP address, v4 or v6
 * @param port_num remote port used to establish the connection
 * @param ec contains potential errors
 * @return a shared pointer to the socket created by the client
 */
/*
boost::shared_ptr<tcp::socket> Client::connect(boost::asio::ip::address addr, unsigned short port_num, boost::system::error_code ec){
	boost::asio::ip::tcp::endpoint ep(addr, port_num);
	return connect(ep, ec);
}
*/

/**
 * Connect the client to addr on port port_num
 *
 * @param addr IP address, v4 or v6
 * @param port_num remote port used to establish the connection
 * @param ec contains potential errors
 * @return a shared pointer to the socket created by the client
 */
/*
boost::shared_ptr<tcp::socket> Client::connect(std::string addr, unsigned short port_num, boost::system::error_code ec){
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(addr), port_num);
	return connect(ep, ec);
}
*/

} /* namespace network */
