/*
 * launch.cpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#include "graphics/Graphics.hpp"
#include "log/Log.hpp"

class Client {
public:
	Client() {
		std::string log("logClient");
		client::Log::init(log);
		client::Log::out("begin ...");
		graphics::Graphics graphics;
	}

};


