/*
 * Database.cpp
 *
 *  Created on: 5 avr. 2013
 *      Author: pierre
 */

#include "Database.hpp"

Database* Database::m_instance = NULL;

Database::Database() : m_mysql(NULL) {

}

bool Database::init(std::string host, std::string login, std::string pass, std::string db) {
	m_instance = new Database();
	getInstance()->m_mysql = mysql_init(NULL);
	if(!mysql_real_connect(getInstance()-> m_mysql, host.c_str(), login.c_str(), pass.c_str(), db.c_str(), 0, NULL, 0)) {
		Log::err("Connection to database failed");
		return false;
	}

	return true;
}

ResultQuery* Database::query(std::string query) {
	if(mysql_query(getInstance()->m_mysql, query.c_str()) == 0)
		return new ResultQuery(mysql_store_result(getInstance()->m_mysql));
	return NULL;
}

void Database::close() {
	 mysql_close(getInstance()->m_mysql);
	 delete m_instance;
	 m_instance = NULL;
	 Log::out("Database connection closed");
}

Database* Database::getInstance() {
	 if(m_instance == NULL) {
		 Log::err("Connection to database closed");
		 exit(0);
	 }
	 return m_instance;
}
