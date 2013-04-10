/*
 * Log.hpp
 *
 *  Created on: 5 avr. 2013
 *      Author: pierre
 */

#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>
#include <iostream>
#include <cstdarg>

class Log {

public:
	static bool init(std::string path);
	static bool init();

	static void out(const std::string &s);
	static void err(const std::string &s);

	static void close();

private:
	Log();
	static Log* getInstance();
	static Log* m_instance;
	std::ofstream* m_file;
};

#endif
