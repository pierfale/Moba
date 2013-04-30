/*
 * MapEditor.cpp
 *
 *  Created on: 19 avr. 2013
 *      Author: Béni
 */

#include "MapEditor.h"

namespace graphics {

MapEditor::MapEditor() {}
MapEditor::~MapEditor() {}

void MapEditor::write(std::string path) {
		std::ofstream f( path.c_str() , std::ios::out | std::ios::binary);
		int h,w, in;
		if(!f.is_open()) { std::cout << "Failed to open the file" << std::endl; }
		else {
			std::cout << "height?"<< std::endl;
			std::cin >> h;
			f.write((char *)&h, sizeof(int));
			std::cout << "width?"<< std::endl;
			std::cin >> w;
			f.write((char *)&w, sizeof(int));
			for (int j = 0 ; j < h ; j++) {
				for (int i = 0 ; i < w ; i++){
					std::cout << util::Cast::intToString(i)+":"+util::Cast::intToString(j) << std::endl;
					std::cin >> in;
					if ( in < 0) { --i; std::cout << "wrong value" << std::endl; }
					else { f.write((char *)&in, sizeof(int)); }
				}
			}
		}
		f.close();
	}

	void MapEditor::full() {
		std::ofstream f( "ressources/game/mapOfArena" , std::ios::out | std::ios::binary);
		int in = 30, tmp = 0;
		if(!f.is_open()) { std::cout << "Failed to open the file" << std::endl; }
		else {
			f.write((char *)&in, sizeof(int));
			f.write((char *)&in, sizeof(int));
			for (int j = 0 ; j < 30 ; j++) {
				for (int i = 0 ; i < 30 ; i++){
					in = 1;
				//	tmp = rand() % 100 + 1;
				//	if (tmp > 90) in = 23;
					if (tmp != 10 && i == 5) {tmp++; in = 23;}
					f.write((char *)&in, sizeof(int));
				}
			}
		}
		f.close();
		in = 0;
		srand (time(NULL));
		std::ofstream g( "ressources/game/mapOfArenaL" , std::ios::out | std::ios::binary);
		if(!g.is_open()) { std::cout << "Failed to open the file" << std::endl; }
		else {
			for (int j = 0 ; j < 30; j++) {
				for (int i = 0 ; i < 30 ; i++){
					in = 0;
					if ( j == 0 ) {
						if ( i == 0 ) in = 6;
						else if ( i == 29) in = 7;
						else in = 4;
					} else if ( j == 29 ) {
						if ( i == 0 ) in = 10;
						else if ( i == 29) in = 11;
						else in = 5;
					} else if ( i == 0 ) {
						if ( j == 0 ) in = 6;
						else if ( j == 29) in = 10;
						else in = 8;
					} else if ( i == 29 ) {
						if ( j == 0 ) in = 7;
						else if ( j == 29) in = 11;
						else in = 9;
					}
					g.write((char *)&in, sizeof(int));
				}
			}
		}
		g.close();
	}

} /* namespace graphics */
