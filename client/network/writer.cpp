/*
 * writer.cpp
 *
 *  Created on: 16 avr. 2013
 *      Author: Carl
 */

#include "writer.h"

namespace network {

writer::writer(boost::asio::ip::tcp::socket& sock) : m_socket(sock){

}

writer::~writer() {
	// TODO Auto-generated destructor stub
}

void writer::write(std::string message){
	boost::asio::async_write(m_socket, boost::asio::buffer(message),
	        boost::bind(&writer::handle_write, this,
	          boost::asio::placeholders::error));
}

void writer::handle_write(boost::system::error_code const & error){
	if (!error){
		// Autres actions éventuelles
	}
	else{
		std::cerr << error.message() << std::endl;
	}
}

} /* namespace network */
