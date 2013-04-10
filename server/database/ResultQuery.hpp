#ifndef RESULTQUERY_H
#define RESULTQUERY_H

#include <string>
#include <map>
#include <winsock.h>
#include <MYSQL/mysql.h>
#include "../log/Log.hpp"

class ResultQuery {

public:
	ResultQuery(MYSQL_RES* result);
	bool next();
	std::string get(int i);
	std::string get(std::string name);
	void free();

private:
	MYSQL_RES* m_result;
	MYSQL_ROW m_row;
	std::map<std::string, int> m_columnsName;
};

#endif
