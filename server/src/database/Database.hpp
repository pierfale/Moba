/*
 * DataBase.hpp
 *
 *  Created on: 5 avr. 2013
 *      Author: pierre
 */

#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#ifdef WIN32
#include <winsock.h>
#endif

#include <mysql/mysql.h>
#include <iostream>
#include "../log/Log.hpp"
#include "ResultQuery.hpp"

class Database {

public:
	static bool init(std::string host, std::string login, std::string pass, std::string db);
	static ResultQuery* query(std::string query);
	static void update(std::string query);
	static void close();
	static int lastInsertID();
private:
	Database();
	static Database* getInstance();
	static Database* m_instance;
	MYSQL* m_mysql;
};

#endif /* DATABASE_HPP_ */
