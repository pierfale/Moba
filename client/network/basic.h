/*
 * basic.h
 *
 *  Created on: 16 avr. 2013
 *      Author: Carl
 */

#ifndef BASIC_H_
#define BASIC_H_

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

namespace network {

class basic {
public:
	virtual ~basic();

	static boost::shared_ptr<boost::asio::ip::tcp::socket> connect(boost::asio::io_service& ios, boost::asio::ip::tcp::endpoint& ep, boost::system::error_code& ec);
	static boost::shared_ptr<boost::asio::ip::tcp::socket> connect(boost::asio::io_service& ios, boost::asio::ip::address addr, unsigned short port_num, boost::system::error_code& ec);
	static boost::shared_ptr<boost::asio::ip::tcp::socket> connect(boost::asio::io_service& ios, std::string addr, unsigned short port_num, boost::system::error_code& ec);

private:
	basic();

};

} /* namespace network */
#endif /* BASIC_H_ */
