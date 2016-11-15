/*
 * ConnectionScreen.hpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#ifndef CONNECTIONSCREEN_HPP_
#define CONNECTIONSCREEN_HPP_

#include <boost/uuid/sha1.hpp>
#include <sstream>
#include "../component/ComponentInclude.hpp"
#include "../GUIStyle.hpp"
#include "../layout/LayoutInclude.hpp"
#include "../../network/Network.hpp"
#include "Packet.hpp"
#include "PacketType.hpp"
#include "../Cursor.hpp"

//Log
#include "../../log/Log.hpp"
//Config
#include "../../config/Config.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class ConnectionScreen : public Container {

	public:
		ConnectionScreen();
		~ConnectionScreen();
		void load();
		void startConnection();
		void setMessage(std::string message);
		void setConnected();
		bool event(sf::Event* event, bool used);
		std::string getComponentName();
		static std::string getName();

	private:
		Container* m_mainContainer;
		Label* m_pseudoLabel;
		TextField* m_pseudoTextField;
		Label* m_passwordLabel;
		TextField* m_passwordTextField;
		Button* m_connectionButton;
		InnerWindow* m_messageInnerWindow;
		Label* m_messageLabel;

	};

}


#endif /* CONNECTIONSCREEN_HPP_ */
