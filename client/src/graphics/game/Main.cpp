/*
 * Main.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: Béni
 */

#include "../../util/Util.hpp"
#include "../game/Gameboard.h"
#include "../game/MapEditor.h"
/*
int main() {
	//graphics::MapEditor::full();
	graphics::Gameboard::loadImage();
	std::vector<util::CoordInt> path = util::PathFinding::getPath(util::CoordInt(1,1),util::CoordInt(10,1));

	for(int i=0; i<game::GameboardModel::getHeight(); i++) {
		for(int j=0; j<game::GameboardModel::getWidth(); j++) {
			bool find = false;
			for(unsigned int k=0; k<path.size(); k++){
				if(path.at(k) == util::CoordInt(j,i))
					find = true;

			}
			if(find)
				std::cout << "X";
			else if(game::GameboardModel::getGameboard(0)[j][i]->getPassable())
				std::cout << " ";
			else
				std::cout << "#";
		}
		std::cout << std::endl;
	}
}
*/
