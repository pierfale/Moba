/*
 * TcpSocket.cpp
 *
 *  Created on: 20 avr. 2013
 *      Author: pierre
 */

#include "TcpSocket.hpp"

namespace network {

	TcpSocket::TcpSocket(boost::asio::io_service* service) : m_socket(*service) {

	}

	boost::asio::ip::tcp::socket* TcpSocket::getSocket() {
		return &m_socket;
	}
}


