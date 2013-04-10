/*
 * ThreadManager.hpp
 *
 *  Created on: 10 avr. 2013
 *      Author: pierre
 */

#ifndef THREADMANAGER_HPP_
#define THREADMANAGER_HPP_

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/function.hpp>
#include <sstream>
#include "log/Log.hpp"

class ThreadManager {

public:
	static void init();
	static void add(const boost::function0<void>& func, std::string funName = "Unknown");
	static int number();
	static boost::thread_group* getThreads();
private:
	ThreadManager();
	static ThreadManager* getInstance();
	static ThreadManager* m_instance;
	boost::thread_group m_threads;


};


#endif /* THREADMANAGER_HPP_ */
