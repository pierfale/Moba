/*
 * PathFinding.cpp
 *
 *  Created on: 29 avr. 2013
 *      Author: Béni
 */

#include "PathFinding.h"

namespace util {

//pathfinding
std::vector<CoordInt> PathFinding::getPath(CoordInt start, CoordInt goal) {
	std::stack<CoordInt> vector;
	std::map<CoordInt, CoordInt> parent;
	parent[start] = start;
	CoordInt curr = start;
	int counter = 0;
	boost::timer t;
	while(curr != goal) {

		std::vector<CoordInt> tmp;
		for(int i=-1; i<2; i++) {
			for(int j=-1; j<2; j++) {
				if(curr.x+i >= 0 && curr.x+i < game::GameboardModel::getWidth() &&
						curr.y+j >= 0 && curr.y+j < game::GameboardModel::getHeight() &&
						game::GameboardModel::getGameboard(0)[curr.x+i][curr.y+j]->getPassable()) {
					counter++;
					CoordInt coord(curr.x+i, curr.y+j);
					if(parent.find(coord) == parent.end()) {
						tmp.push_back(coord);
						parent[coord] = curr;
					}
				}
			}
		}
		//bad tri
		for(int i=0; i<(int)tmp.size()-1;i++) {
			int min = i;
			for(int j=i+1; j<(int)tmp.size(); j++) {
				counter++;
				if((tmp.at(j).x > goal.x ? tmp.at(j).x - goal.x : goal.x - tmp.at(j).x)
    				+(tmp.at(j).y > goal.y ? tmp.at(j).y - goal.y : goal.y - tmp.at(j).y)
    				< (tmp.at(min).x > goal.x ? tmp.at(min).x - goal.x : goal.x - tmp.at(min).x)
    				+(tmp.at(min).y > goal.y ? tmp.at(min).y - goal.y : goal.y - tmp.at(min).y)) {
					min = j;
				}
				if(min != i) {
					std::swap(tmp[j], tmp[min]);

				}
			}
		}


		for(unsigned int i=0; i<tmp.size(); i++) {
			vector.push(tmp.at(i));
		}
		curr = vector.top();
		vector.pop();
	}
	std::cout << "COUNTER : " << counter << std::endl;
	std::cout << "TIMER : " << t.elapsed() << std::endl;
	std::vector<CoordInt> r;
	while(parent[curr] != curr) {
		r.push_back(curr);
		curr = parent[curr];
	}
	return r;
}

void PathFinding::printPath(std::vector<CoordInt> path) {
	for (std::vector<CoordInt>::iterator it = path.begin() ; it != path.end() ; ++it)
		std::cout << (*it).toString() << std::endl;
}

} /* namespace util */
