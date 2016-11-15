/*
 * TcpSocket.hpp
 *
 *  Created on: 20 avr. 2013
 *      Author: pierre
 */

#ifndef TCPSOCKET_HPP_
#define TCPSOCKET_HPP_

#include <boost/asio.hpp>

namespace network {

	class TcpSocket {

	public:
		TcpSocket(boost::asio::io_service* service);
		boost::asio::ip::tcp::socket* getSocket();

	private:
		boost::asio::ip::tcp::socket m_socket;
	};
}


#endif /* TCPSOCKET_HPP_ */
