/*
 * client.cpp
 *
 *  Created on: 17 avr. 2013
 *      Author: Carl
 */


#include "client.h"

client::client(std::string addr, unsigned int port_num) : _socket(_io_service), _io_manager(_socket){
	connect(addr, port_num);
	_io_service.run();
}

client::~client() {
	// TODO Auto-generated destructor stub
}

void client::connect(std::string addr, unsigned short port_num){
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(addr), port_num);

	_socket.async_connect(ep,
			boost::bind(&client::handle_connect, this,
			boost::asio::placeholders::error)
			);
}

void client::handle_connect(const boost::system::error_code& error){
	if(error){
		std::cerr << "failed to connect: " << error.message() << std::endl;
	}
	else{
		std::cout << "connected to " << _socket.remote_endpoint().address() << ":" << _socket.remote_endpoint().port() << std::endl;
		read();
	}
}

void client::read(){
	_io_manager.async_read(_message_read, boost::bind(&client::handle_read, this,
			boost::asio::placeholders::error));
}

void client::handle_read(const boost::system::error_code& error){
	if (!error){
		// Traitement sur l'attribut _message_read...
		//...


		read();
	}
	else{
		std::cerr << error.message() << std::endl;
	}
}

void client::write(const network::message& msg){
	_io_manager.async_write(_message_written, boost::bind(&client::handle_write, this,
				boost::asio::placeholders::error));
}

void client::handle_write(const boost::system::error_code& error){
	if (!error){
		// Traitement sur l'attribut _message_written...
		//...

		read();
	}
	else{
		std::cerr << error.message() << std::endl;
	}
}
