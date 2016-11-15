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
#include "game/skill/SkillReader.hpp"
#include "game/spell/SpellReader.hpp"

int main() {



	std::cout << "Init client ..." << std::endl;
	Config::load("client.conf");

	std::string log(Config::get("log"));
	std::cout << "Log file : " << log << std::endl;
	Log::init(log);

	game::SpellReader spr;
	if(!spr.load("ressources/game/spell.dat"))
		return -1;

	game::SkillReader skr;
	if(!skr.load("ressources/game/skill.dat"))
		return -1;

	graphics::Graphics::init();
	graphics::Graphics::run();
}


