/*
 * Launch.cpp
 *
 *  Created on: 20 avr. 2013
 *      Author: pierre
 */

#include "network/Server.hpp"
#include "log/Log.hpp"
#include "database/Database.hpp"
#include "config/Config.hpp"
#include "skill/SkillReader.hpp"

int main() {
	std::cout << "Init server ..." << std::endl;
	Config config;
	config.load("serv.conf");

	std::string log(config.get("log"));
	std::cout << "Log file : " << log << std::endl;
	Log::init(log);

	log_out "Connect to database ("+config.get("dbhost")+","+config.get("dbuser")+","+config.get("dbpass")+","+config.get("dbname")+") ..." end_log_out;

	if(Database::init(config.get("dbhost"), config.get("dbuser"), config.get("dbpass"), config.get("dbname")))
		log_out "Connection established !" end_log_out;
	else {
		log_err "Connection failed !" end_log_err;
		return -1;
	}

	network::Server::init(2342);

	if(SkillReader::load(config.get("skill")))
		log_out "Skill loaded" end_log_out;
	else {
		log_err "Read skill failed" end_log_err;
		return -1;
	}

	network::Server::run();
}


