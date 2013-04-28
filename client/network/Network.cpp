/*
 * Network.cpp
 *
 *  Created on: 21 avr. 2013
 *      Author: pierre
 */

#include "Network.hpp"

namespace network {

	boost::shared_ptr<Network> Network::m_instance;

	Network::Network() : m_run(true), m_firstConnect(true) {

	}

	void Network::init(boost::asio::ip::tcp::endpoint target) {
		getInstance()->m_run = true;
		getInstance()->m_socket.reset(new boost::asio::ip::tcp::socket(getInstance()->m_ios));
		getInstance()->m_socket.get()->async_connect(target,
				boost::bind(&Network::connect_handle, getInstance(), boost::asio::placeholders::error));
		if(getInstance()->m_firstConnect) {
			getInstance()->m_ios.run();
			getInstance()->m_firstConnect = false;
		}
	}

	void Network::connect_handle(const boost::system::error_code& error) {
		if(!error) {
			log_out "Connected to the server!" end_log_out;
			boost::thread thread(boost::bind(&Network::run, this));
		}
		else {
			log_err error.message() end_log_err;
		}
	}

	void Network::close() {
		network::Packet packet(getInstance()->m_socket.get(), network::PacketType::SESSION_CLOSE);
		packet.send(boost::bind(&Network::close_handle, getInstance()));
	}

	void Network::close_handle() {
		getInstance()->m_run = false;
		getInstance()->m_socket.get()->close();
		getInstance()->m_socket.reset();
		graphics::Graphics::getWindow()->addCallFunction(boost::bind(&game::PlayerList::clear));
	}

	boost::asio::ip::tcp::socket* Network::getSocket() {
		return getInstance()->m_socket.get();
	}

	bool Network::isRunning() {
		return getInstance()->m_run;
	}

	void Network::run() {
		while(Network::isRunning()) {
			network::Packet packet(m_socket.get(), network::PacketType::UNDEFINED);
			if(!packet.receive())
				break;
			log_out "packet receive! type="+util::Cast::intToString(packet.getType()) end_log_out;
			int typeFirstMask = 0xFF000000;
			if((packet.getType() & typeFirstMask) == network::PacketType::SESSION) {
				Message_session::process(packet);
			}
		}
		log_out "disconnected from the server" end_log_out;
	}

	Network* Network::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new Network());
		return m_instance.get();
	}


}


