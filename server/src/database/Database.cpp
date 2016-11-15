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
		log_err "Connection to database failed" end_log_err;
		std::cerr << mysql_error(getInstance()->m_mysql) << std::endl;
		return false;
	}

	return true;
}

ResultQuery* Database::query(std::string query) {
	log_out "query : "+query end_log_out;
	if(mysql_query(getInstance()->m_mysql, query.c_str()) == 0)
		return new ResultQuery(mysql_store_result(getInstance()->m_mysql));
	log_err "Error SQL : "+std::string(mysql_error(getInstance()->m_mysql)) end_log_err;
	return NULL;
}

void Database::update(std::string query) {
	log_out "query : "+query end_log_out;
	if(mysql_query(getInstance()->m_mysql, query.c_str()) != 0)
		log_err "Error SQL : "+std::string(mysql_error(getInstance()->m_mysql)) end_log_err;
}

void Database::close() {
	 mysql_close(getInstance()->m_mysql);
	 delete m_instance;
	 m_instance = NULL;
	 Log::out("Database connection closed");
}

int Database::lastInsertID() {
	return mysql_insert_id(getInstance()->m_mysql);
}

Database* Database::getInstance() {
	 if(m_instance == NULL) {
		 Log::err("Connection to database closed");
		 exit(0);
	 }
	 return m_instance;
}
