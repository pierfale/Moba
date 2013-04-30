/*
 * MapEditor.h
 *
 *  Created on: 19 avr. 2013
 *      Author: Béni
 */

#ifndef MAPEDITOR_H_
#define MAPEDITOR_H_

#include <stdlib.h>
#include <time.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "../../util/Cast.hpp"

namespace graphics {

	class MapEditor {
	public:
		MapEditor();
		virtual ~MapEditor();
		static void full();
		static void write(std::string path);
	};

} /* namespace game */
#endif /* MAPEDITOR_H_ */
