/*
 * Network.hpp
 *
 *  Created on: 21 avr. 2013
 *      Author: pierre
 */

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include "Packet.hpp"
#include "PacketType.hpp"
#include "message/Message_session.hpp"

#include "../log/Log.hpp"
#include "../util/Util.hpp"

namespace network {

	class Network {

	public:
		static void init(boost::asio::ip::tcp::endpoint target);
		static void close();
		static boost::asio::ip::tcp::socket* getSocket();
		static bool isRunning();
		void run();
		void close_handle();
	private:
		Network();
		static Network* getInstance();
		void connect_handle(const boost::system::error_code& error);
		static boost::shared_ptr<Network> m_instance;
		boost::asio::io_service m_ios;
		boost::shared_ptr<boost::asio::ip::tcp::socket> m_socket;
		bool m_run;
		bool m_firstConnect;

	};
}


#endif /* NETWORK_HPP_ */
