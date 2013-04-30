/*
 * Network.cpp
 *
 *  Created on: 21 avr. 2013
 *      Author: pierre
 */

#include "Network.hpp"
#include "../graphics/screen/ConnectionScreen.hpp"
#include "../graphics/screen/ScreenManager.hpp"

namespace network {

	boost::shared_ptr<Network> Network::m_instance;
	boost::mutex Network::m_guard;

	Network::Network() : m_run(true), m_firstConnect(true) {

	}

	bool Network::init(boost::asio::ip::tcp::endpoint target) {
		getInstance()->m_run = true;
		getInstance()->m_socket.reset(new boost::asio::ip::tcp::socket(getInstance()->m_ios));
		boost::system::error_code error;
		getInstance()->m_socket.get()->connect(target, error);
		if(error) {
			if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() == graphics::ConnectionScreen::getName())
				((graphics::ConnectionScreen*)graphics::Graphics::getWindow()->getContentPane())->setMessage("Unable to connect to the server");
			return false;
		}
		else {
			log_out "Connected to the server!" end_log_out;
			boost::thread thread(boost::bind(&Network::run, getInstance()));
		}
		return true;
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
		packet.send();
		getInstance()->m_run = false;
		getInstance()->m_socket.get()->close();
		getInstance()->m_socket.reset();
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
			m_guard.lock();
			getInstance()->m_packetStack.push_back(packet);
			m_guard.unlock();


		}

		close_handle();
	}

	void Network::process() {
		m_guard.lock();
		for(unsigned int i=0; i<getInstance()->m_packetStack.size(); i++) {
			log_err "packet receive! type="+util::Cast::intToString(getInstance()->m_packetStack.at(i).getType()) end_log_err;
			int typeFirstMask = 0xFF000000;
			if((getInstance()->m_packetStack.at(i).getType() & typeFirstMask) == network::PacketType::SESSION) {
				Message_session::process(getInstance()->m_packetStack.at(i));
			}
		}
		getInstance()->m_packetStack.clear();
		m_guard.unlock();
	}

	void Network::close_handle() {
		log_out "disconnected from the server" end_log_out;
		if(graphics::Graphics::getWindow()->getContentPane()->getComponentName() != graphics::ConnectionScreen::getName()) {
			graphics::Graphics::getWindow()->setContentPane(graphics::ScreenManager::connection());
			graphics::Graphics::getWindow()->getContentPane()->validate();
			((graphics::ConnectionScreen*)graphics::Graphics::getWindow()->getContentPane())->setMessage("Disconnected from server");
		}
	}

	Network* Network::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new Network());
		return m_instance.get();
	}


}


