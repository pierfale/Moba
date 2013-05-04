/*
 * Chat.hpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#ifndef CHAT_HPP_
#define CHAT_HPP_

#include "../component/ComponentInclude.hpp"
#include "../GUIStyle.hpp"
#include "../layout/LayoutInclude.hpp"

namespace graphics {

	class Chat : public Container {

	public:
		Chat();
		~Chat();
		void setID(int id);
		int getID();
		void send(void* origin);
		void receive(std::string message);

	private:
		int m_id;
		BasicStyle* m_labelStyle;
		ScrollBar* m_scroll;
		Label* m_label;
		Container* m_botContainer;
		TextField* m_textField;
		Button* m_button;

	};
}


#endif /* CHAT_HPP_ */
