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
#include "../../graphics/inheritedComponent/Chat.hpp"

namespace game {

	class ChatList {

	public:
		static void add(graphics::Chat* chat);
		static graphics::Chat* getByID(int id);
		static void removeByID(int id);

	private:
		ChatList();
		static ChatList* getInstance();
		static boost::shared_ptr<ChatList> m_instance;
		boost::ptr_vector<graphics::Chat> m_list;


	};
}


#endif /* CHATLIST_HPP_ */
