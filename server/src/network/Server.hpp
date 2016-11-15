/*
 * Server.hpp
 *
 *  Created on: 20 avr. 2013
 *      Author: pierre
 */

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "TcpSocket.hpp"
#include "../client/Client.hpp"
#include "../util/Util.hpp"
#include "../log/Log.hpp"
#include "Packet.hpp"
#include "PacketType.hpp"

namespace network {

	class Server {

	public:
		static void init(int port);
		static void run();
		static void sendAll(Packet packet);
		static void removeClient(Client* client);
		static Client* getClientByID(int id);

	private:
		Server();
		static Server* getInstance();
		static boost::shared_ptr<Server> m_instance;
		void accept();
		void accept_handle(TcpSocket* socket, const boost::system::error_code& error);
		boost::asio::io_service m_ios;
		boost::asio::ip::tcp::acceptor* m_acceptor;
		boost::ptr_vector<Client> m_clients;
	};
}


#endif /* SERVER_HPP_ */
