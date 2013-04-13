/*
 * launch.cpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#include "graphics/Graphics.hpp"
#include "log/Log.hpp"

#include "game/skill/SkillReader.hpp"

class Client {
public:
	Client() {
		std::string log("client.log");
		client::Log::init(log);
		client::Log::out("begin ...");
		game::SkillReader sr;
		sr.load("ressources/game/skill.dat");
		graphics::Graphics graphics;
	}

};


