/*
 * ChatList.cpp
 *
 *  Created on: 3 mai 2013
 *      Author: pierre
 */

#include "ChatList.hpp"

namespace game {

	boost::shared_ptr<ChatList> ChatList::m_instance;


	ChatList::ChatList() {

	}

	void ChatList::add(graphics::Chat* chat) {
		getInstance()->m_list.push_back(chat);
	}

	graphics::Chat* ChatList::getByID(int id) {
		for(boost::ptr_vector<graphics::Chat>::iterator it = getInstance()->m_list.begin(); it != getInstance()->m_list.end(); ++it) {
			if(it->getID() == id)
				return &(*it);
		}
		return NULL;
	}

	void ChatList::removeByID(int id) {
		for(boost::ptr_vector<graphics::Chat>::iterator it = getInstance()->m_list.begin(); it != getInstance()->m_list.end(); ++it) {
			if(it->getID() == id) {
				getInstance()->m_list.release(it).release();
				return;
			}
		}
	}

	ChatList* ChatList::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new ChatList());
		return m_instance.get();
	}

}


