/*
 * ChatList.hpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#ifndef CHATLIST_HPP_
#define CHATLIST_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "Chat.hpp"

class ChatList {

public:
	~ChatList();
	static void add(Chat* chat);
	static int getNextID();
	static Chat* getByID(int id);

private:
	ChatList();
	static ChatList* getInstance();
	static boost::shared_ptr<ChatList> m_instance;
	int m_nextID;
	boost::ptr_vector<Chat> m_list;
};


#endif /* CHATLIST_HPP_ */
