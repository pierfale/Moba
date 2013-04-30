/*
 * writer.h
 *
 *  Created on: 16 avr. 2013
 *      Author: Carl
 */

#ifndef WRITER_H_
#define WRITER_H_

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

namespace network {

class writer {
public:
	writer(boost::asio::ip::tcp::socket & sock);
	virtual ~writer();

	void write(std::string message);

private:
	void handle_write(boost::system::error_code const & error);
	boost::asio::ip::tcp::socket& m_socket;
};

} /* namespace network */
#endif /* WRITER_H_ */
