/*
 * reader.h
 *
 *  Created on: 16 avr. 2013
 *      Author: Carl
 */

#ifndef READER_H_
#define READER_H_

#define BUFFER_SIZE	128

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace network {

class reader {
public:
	reader(boost::asio::ip::tcp::socket & sock);
	virtual ~reader();

	void read();

private:
	void handle_read(const boost::system::error_code& error, size_t number_bytes_read);

	boost::asio::ip::tcp::socket& m_socket;
	boost::array<char, BUFFER_SIZE> m_network_buffer;
};


} /* namespace network */
#endif /* READER_H_ */
