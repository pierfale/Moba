/*
 * Log.hpp
 *
 *  Created on: 5 avr. 2013
 *      Author: pierre
 */

#ifndef CLIENT_LOG_HPP
#define CLIENT_LOG_HPP

#define log_out Log::out(
#define end_log_out )
#define log_err Log::err(
#define end_log_err , __FILE__, __LINE__)

#include <fstream>
#include <iostream>
#include <cstdarg>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <sstream>


class Log {

public:
	~Log();
	static bool init(std::string path);
	static bool init();

	static void out(const std::string &s);
	static void err(const std::string &s, const char* file = "undef", int line = 0);

	static void close();

private:
	Log();
	static Log* getInstance();
	static boost::shared_ptr<Log> m_instance;
	std::ofstream* m_file;
};

#endif
