/*
 * launch.cpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */
#include <boost/asio.hpp>

#include "graphics/Graphics.hpp"
#include "log/Log.hpp"
#include "config/Config.hpp"
#include "iomanager.cpp"
#include "game/skill/SkillReader.hpp"

int main() {

	std::cout << "Init client ..." << std::endl;
	Config::load("client.conf");

	std::string log(Config::get("log"));
	std::cout << "Log file : " << log << std::endl;
	Log::init(log);

	game::SkillReader sr;
	sr.load("ressources/game/skill.dat");

	graphics::Graphics::init();
	graphics::Graphics::run();
}


