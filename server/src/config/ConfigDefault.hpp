/*
 * ConfigDefault.hpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#ifndef CONFIGDEFAULT_HPP_
#define CONFIGDEFAULT_HPP_

#include <map>
#include <string>
#include <fstream>

class ConfigDefault {
public:
	static void init();
	static void fillIn(std::map<std::string, std::string>* values);
	static void generate(std::string path);

private:
	ConfigDefault();
	static ConfigDefault* getInstance();
	static ConfigDefault* m_instance;
	std::map<std::string, std::string> m_values;
};


#endif /* CONFIGDEFAULT_HPP_ */
