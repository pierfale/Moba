/*
 * ConfigDefault.cpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#include "ConfigDefault.hpp"

ConfigDefault* ConfigDefault::m_instance = NULL;

ConfigDefault::ConfigDefault() {

}

void ConfigDefault::init() {
	m_instance = new ConfigDefault();
	getInstance()->m_values["dbhost"] = "127.0.0.1";
	getInstance()->m_values["dbuser"] = "root";
	getInstance()->m_values["dbpass"] = "";
	getInstance()->m_values["dbname"] = "db";

	getInstance()->m_values["log"] = "server.log";

	getInstance()->m_values["skill"] = "ressources/skill.dat";
}

void ConfigDefault::fillIn(std::map<std::string, std::string>* values) {
	for(std::map<std::string,std::string>::const_iterator it =  getInstance()->m_values.begin(); it != getInstance()->m_values.end();++it) {
		if(values->find(it->first) == values->end()) {
			(*values)[it->first] = it->second;
		}
	}
}

void ConfigDefault::generate(std::string path) {
	std::ofstream file(path.c_str(), std::ios::out | std::ios::trunc);
	unsigned int length = 80;
	unsigned int headerHeight = 5;
	std::string title = "Moba v0.1";
	//generate header
	for(unsigned int j=0; j<headerHeight; j++) {
		for(unsigned int i=0; i<length; i++) {

			if(j == 2 && i > (length-title.length())/2-1 && i < (length-title.length())/2+title.length())
				file.put(title.at(i-(length-title.length())/2));
			else if(i==0 || i == length-1 || j == 0 || j == headerHeight-1)
				file.put('#');
			else
				file.put(' ');
		}
		file.put('\n');
	}
	for(std::map<std::string,std::string>::const_iterator it =  getInstance()->m_values.begin(); it != getInstance()->m_values.end();++it) {
		file << it->first << "=" << it->second << std::endl;
	}

}

ConfigDefault* ConfigDefault::getInstance() {
	if(m_instance == NULL)
		init();
	return m_instance;
}

