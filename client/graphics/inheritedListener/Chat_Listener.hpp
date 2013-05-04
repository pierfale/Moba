/*
 * Chat_Listener.hpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#ifndef CHAT_LISTENER_HPP_
#define CHAT_LISTENER_HPP_

#include "../listener/ButtonListener.hpp"
#include "../inheritedComponent/Chat.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class Chat_ButtonListener : public ButtonListener {

	public:
		Chat_ButtonListener(Chat* view);
		void pressed(void* origin);
		void enter(void* origin);

	private:
		Chat* m_view;
	};

	class Chat_TextFieldListener : public TextFieldListener {

	public:
		Chat_TextFieldListener(Chat* view);
		void enter(void* origin);

	private:
		Chat* m_view;
	};


}


#endif /* CHAT_LISTENER_HPP_ */
