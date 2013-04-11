/*
 * launch.cpp
 *
 *  Created on: 5 avr. 2013
 *      Author: pierre
 */

#include <iostream>
#include <boost/thread.hpp>
#include "log/log.hpp"
#include "database/Database.hpp"
#include "config/Config.hpp"
#include "../client/ThreadManager.hpp"


//tmp
#include "../client/Launch.cpp"

int main() {
	//tmp
	Client c;

	while(ThreadManager::number() > 0) {
		boost::this_thread::sleep(boost::posix_time::milliseconds(50));
	}

	//ThreadManager::getThreads()->join_all();
	exit(0);

	std::cout << "Launch server ..." << std::endl;
	Config config;
	config.load("serv.conf");

	std::string log(config.get("log"));
	std::cout << "Log file : " << log << std::endl;
	Log::init(log);

	Log::out("Connect to database ("+config.get("dbhost")+","+config.get("dbuser")+","+config.get("dbpass")+","+config.get("dbname")+") ...");

	if(Database::init(config.get("dbhost"), config.get("dbuser"), config.get("dbpass"), config.get("dbname")))
		Log::out("Connection established !");
	else
		return -1;

	//test
	ResultQuery* rq = Database::query("SELECT * FROM account");
	while(rq->next()) {
		std::cout << rq->get("Account_Pseudo") << std::endl;
	}
	rq->free();

	Database::close();
	Log::close();

	return 0;
}


