/*
 * reader.cpp
 *
 *  Created on: 16 avr. 2013
 *      Author: Carl
 */

#include "reader.h"

namespace network {

reader::reader(boost::asio::ip::tcp::socket& sock) : m_socket(sock){

}

reader::~reader() {
	// TODO Auto-generated destructor stub
}

void reader::read(){
	boost::asio::async_read(m_socket,
			boost::asio::buffer(m_network_buffer, BUFFER_SIZE),
			boost::bind(&reader::handle_read, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
}

void reader::handle_read(const boost::system::error_code& error, size_t number_bytes_read){
	if (!error){
		std::cout.write(&m_network_buffer[0], number_bytes_read);
		read();
	}
	else{
		std::cerr << error.message() << std::endl;
	}
}

} /* namespace network */
