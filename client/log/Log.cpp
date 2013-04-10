/*
 * Log.cpp
 *
 *  Created on: 5 avr. 2013
 *      Author: pierre
 */

#include "Log.hpp"



namespace client {

	Log* Log::m_instance = NULL;

	Log::Log() : m_file(NULL) {

	}

	bool Log::init(std::string path) {
		m_instance = new Log();
		getInstance()->m_file = new std::ofstream(path.c_str(), std::ios::out | std::ios::trunc);
		if(!getInstance()->m_file) {
			std::cout << "Error : unable to open " << path << std::endl;
			getInstance()->m_file = NULL;
			return false;
		}
		return true;
	}

	bool Log::init() {
		m_instance = new Log();
		return true;
	}

	void Log::out(const std::string &s) {
		std::stringstream ss1;
		ss1 << boost::this_thread::get_id();
		std::cout << "Thread " << ss1.str() << " : " << s << std::endl;
		fflush(0);
		if(getInstance()->m_file != NULL) {
			*getInstance()->m_file << "Thread " << ss1.str() << " : " <<  s << std::endl;
		}
	}

	void Log::err(const std::string &s) {
		std::cout << "[Error] " << s << std::endl;
		fflush(0);
		if(getInstance()->m_file != NULL) {
			*getInstance()->m_file  << "[Error] " << s << std::endl;
		}
	}

	void Log::close() {
		if(getInstance()->m_file != NULL) {
			getInstance()->m_file->close();
			 delete getInstance()->m_file;
		}
		 if(m_instance != NULL) {
			 delete m_instance;
		 }
		 m_instance = NULL;
		 std::cout << "log closed" << std::endl;

	}

	Log* Log::getInstance() {
		 if(m_instance == NULL) {
			 Log::init();
		 }
		 return m_instance;
	}

}

