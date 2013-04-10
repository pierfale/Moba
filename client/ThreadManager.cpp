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
	std::cout << "oki1" << std::endl;
	boost::thread* t = getInstance()->m_threads.create_thread(fun);
	std::stringstream ss;
	ss << t->get_id();
	client::Log::out("thread launched ID="+ss.str()+" in "+funName);
}

boost::thread_group* ThreadManager::getThreads() {
	return &getInstance()->m_threads;
}

int ThreadManager::number() {
	return getInstance()->m_threads.size();
}
