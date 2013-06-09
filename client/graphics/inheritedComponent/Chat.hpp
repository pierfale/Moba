/*
 * Chat.hpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#ifndef CHAT_HPP_
#define CHAT_HPP_

#include <boost/ptr_container/ptr_vector.hpp>
#include "../component/ComponentInclude.hpp"
#include "../GUIStyle.hpp"
#include "../layout/LayoutInclude.hpp"

#define CHAT_DEFAULT 0
#define CHAT_FULLTEXTFIELD 1

namespace graphics {

	class Chat : public Container {

	public:
		Chat(int type = CHAT_DEFAULT);
		~Chat();
		void setID(int id);
		int getID();
		void send(void* origin);
		void receive(std::string message);

	private:
		int m_id;
		ScrollBar* m_scroll;
		boost::ptr_vector<String> m_string;
		Container* m_stringContainer;
		Container* m_botContainer;
		TextField* m_textField;
		Button* m_button;

	};
}


#endif /* CHAT_HPP_ */
