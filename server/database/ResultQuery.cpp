/*
 * ResultQuery.cpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#include "ResultQuery.hpp"

ResultQuery::ResultQuery(MYSQL_RES* result) : m_result(result), m_row(NULL) {
	int i = 0;
	MYSQL_FIELD *field;
	while((field = mysql_fetch_field(m_result))) {
		m_columnsName[field->name] = i;
		i++;
	}
}

bool ResultQuery::next() {
	m_row = mysql_fetch_row(m_result);

	if(m_row == NULL)
		return false;
	return true;
}

std::string ResultQuery::get(int i) {
	if(m_row != NULL) {
		return m_row[i];
	}
	else {
		Log::err("Row was empty");
	}
	return "";
}

std::string ResultQuery::get(std::string name) {
	if(m_columnsName.find(name) == m_columnsName.end()) {
		Log::err("column not found "+name);
		return "";
	}
	return get(m_columnsName[name]);
}
void ResultQuery::free() {
	 mysql_free_result(m_result);
}
