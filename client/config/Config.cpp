/*
 * Config.cpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#include "Config.hpp"

boost::shared_ptr<Config> Config::m_instance;

Config::Config() {

}

bool Config::load(std::string path) {
	std::ifstream file(path.c_str(), std::ios::in);
	if(!file) {
		Log::err("Unable to open "+path);
		ConfigDefault::fillIn(&getInstance()->m_values);
		return false;
	}

	std::string line;
	while(std::getline(file, line))  {
		getInstance()->evalLine(line);
	}
	ConfigDefault::fillIn(&getInstance()->m_values);
	return true;
}

std::string Config::get(std::string key) {
	if(getInstance()->m_values.find(key) == getInstance()->m_values.end()) {
		Log::err("could not find key "+key);
		return "";
	}
	return getInstance()->m_values[key];
}

void Config::evalLine(std::string line) {
	unsigned int i = nextCharacter(line, 0);
	if(i < line.length() && line.at(i) != '#') {
		unsigned int end = i+1;
		while(end < line.length() && line.at(end) != '=' && !isblank(line.at(end))) {
			end++;
		}
		if(end < line.length()) {
			std::string key = line.substr(i, end);
			i = end;
			while(i < line.length() && line.at(i) != '=') {
				i++;
			}
			if(end < line.length()) {
				i = nextCharacter(line, i+1);
				std::string value;
				if(line.at(i) == '"') {
					end = i+1;
					while(end < line.length() && line.at(end) != '"') {
						end++;
					}
					value = line.substr(i+1, end-2);
				}
				else {
					end = i+1;
					while(end < line.length() && !isblank(line.at(end))) {
						end++;
					}
					value = line.substr(i, end);
				}
				m_values[key] = value;
			}

		}
	}
}

unsigned int Config::nextCharacter(std::string line, unsigned int curr) {
	while(curr < line.length() && isblank(line.at(curr))) {
		curr++;
	}
	if(curr == line.length())
		return 0;
	else
		return curr;
}

bool Config::isblank(char c) {
	char blank [] = {' ', '\t'};
	for(int i=0; i<2; i++) {
		if(c == blank[i])
			return true;
	}
	return false;
}

Config* Config::getInstance() {
	if(m_instance.get() == NULL)
		m_instance.reset(new Config());
	return m_instance.get();
}
