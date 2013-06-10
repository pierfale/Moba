/*
 * Config.hpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <fstream>
#include <map>

#include <boost/shared_ptr.hpp>

#include "../Log/Log.hpp"
#include "ConfigDefault.hpp"

class Config {

public:

	static bool load(std::string path);
	static std::string get(std::string key);

private:
	Config();
	static Config* getInstance();
	static boost::shared_ptr<Config> m_instance;

	void evalLine(std::string line);
	unsigned int nextCharacter(std::string line, unsigned int curr);
	bool isblank(char c);
	std::map<std::string, std::string> m_values;
};

#endif /* CONFIG_HPP_ */
