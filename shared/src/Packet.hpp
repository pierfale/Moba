/*
 * Packet.hpp
 *
 *  Created on: 20 avr. 2013
 *      Author: pierre
 */

#ifndef PACKET_HPP_
#define PACKET_HPP_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>


#include "PacketType.hpp"

#define PACKET_BUFFER_ALLOC 1024
namespace network {

	class Packet {

	public:
		Packet(boost::asio::ip::tcp::socket* socket, PacketType::PacketTypeFinal type);
		void setSocket(boost::asio::ip::tcp::socket* socket);
		void send();
		bool receive();
		PacketType::PacketTypeFinal getType();
		void display();

		Packet& operator<<(int i);
		Packet& operator<<(float i);
		Packet& operator<<(std::string s);


		Packet& operator>>(int* i);
		Packet& operator>>(float* i);
		Packet& operator>>(std::string* s);

	private:
		boost::asio::ip::tcp::socket* m_socket;
		PacketType::PacketTypeFinal m_type;
		char* m_buffer;
		unsigned int m_bufferAllocSize;
		unsigned int m_bufferCurrSize;

		unsigned int m_readerCursor;
		std::string m_message;

	};

}


#endif /* PACKET_HPP_ */
