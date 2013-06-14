/*
 * ThreadManager.cpp
 *
 *  Created on: 10 avr. 2013
 *      Author: pierre
 */

#include "ThreadManager.hpp"
#include "util/Util.hpp"

ThreadManager* ThreadManager::m_instance = NULL;

ThreadManager::ThreadManager() {

}

ThreadManager* ThreadManager::getInstance() {
	if(m_instance == NULL)
		m_instance = new ThreadManager();
	return m_instance;
}

void ThreadManager::add(const boost::function0<void>& fun, std::string funName) {
	boost::thread* t = getInstance()->m_threads.create_thread(fun);
	std::stringstream ss;
	ss << t->get_id();
	log_out "thread launched ID="+ss.str()+" in "+funName end_log_out;
}

boost::thread_group* ThreadManager::getThreads() {
	return &getInstance()->m_threads;
}

int ThreadManager::number() {
	return getInstance()->m_threads.size();
}
