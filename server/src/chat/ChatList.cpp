/*
 * ChatList.cpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#include "ChatList.hpp"

boost::shared_ptr<ChatList> ChatList::m_instance;

ChatList::ChatList() : m_nextID(1) {

}

ChatList::~ChatList() {
	while(m_list.size() > 0)
		m_list.release(m_list.begin()).release();
}

void ChatList::add(Chat* chat) {
	getInstance()->m_list.push_back(chat);
}

int ChatList::getNextID() {
	return getInstance()->m_nextID++;
}

Chat* ChatList::getByID(int id) {
	for(boost::ptr_vector<Chat>::iterator it = getInstance()->m_list.begin(); it != getInstance()->m_list.end(); ++it) {
		if(it->getID() == id)
			return &(*it);
	}
	return NULL;
}

ChatList* ChatList::getInstance() {
	if(m_instance.get() == NULL)
		m_instance.reset(new ChatList());
	return m_instance.get();
}


