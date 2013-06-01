/*
 * PathFinding.cpp
 *
 *  Created on: 29 avr. 2013
 *      Author: Béni
 */

#include "PathFinding.h"
#include "../game/game/GameboardModel.h"

namespace util {

//pathfinding
std::vector<CoordInt> PathFinding::getPath(CoordInt start, CoordInt goal) {

	if(!(start.x >= 0 && start.x < game::GameboardModel::getWidth() &&
		start.y >= 0 && start.y < game::GameboardModel::getHeight()) ||
		!(goal.x >= 0 && goal.x < game::GameboardModel::getWidth() &&
		goal.y >= 0 && goal.y < game::GameboardModel::getHeight())) {
		log_err "invalide coordinates : start "+start.toString()+", goal "+goal.toString() end_log_err;
		std::vector<CoordInt> r;
		return r;
	}
	if(!game::GameboardModel::getGameboard(0)[goal.x][goal.y]->getPassable()) {
		std::vector<CoordInt> r;
		return r;
	}
	std::cout << start.toString() << '-' << goal.toString() << std::endl;
	std::queue<CoordInt> vector;

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
					bool ok = true;
					/*
					if(i != 0 || j != 0) {
						for(int k=-1; k<2; k++) {
							for(int l=-1; l<2; l++) {
								if((k == 0 || l == 0) && !(k == 0 && l == 0)) {
									if(curr.x+i+k >= 0 && curr.x+i+k < game::GameboardModel::getWidth() &&
										curr.y+j+l >= 0 && curr.y+j+l < game::GameboardModel::getHeight()) {
										if(!game::GameboardModel::getGameboard(0)[curr.x+i+k][curr.y+j+l]->getPassable())
											ok = false;
									}
								}
							}
						}
					}
*/
					if(ok) {
						counter++;
						CoordInt coord(curr.x+i, curr.y+j);
						if(parent.find(coord) == parent.end()) {
							tmp.push_back(coord);
							parent[coord] = curr;
						}
					}
				}
			}
		}
		/*
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

*/
		for(unsigned int i=0; i<tmp.size(); i++) {
			vector.push(tmp.at(i));
		}
		curr = vector.front();
		vector.pop();
	}
	std::cout << "COUNTER : " << counter << std::endl;
	std::cout << "TIMER : " << t.elapsed() << std::endl;
	std::vector<CoordInt> path;
	while(parent[curr] != curr) {
		path.push_back(curr);
		curr = parent[curr];
	}
/*
	std::vector<CoordInt> r1 = checkDirection(path);
	std::vector<CoordInt> r;

	for(unsigned int i = 0; i<r1.size()-1; i++) {
		std::cout << "=>" << r1.at(i).toString() << std::endl;
		std::vector<CoordInt> r2 = getPath(r1.at(i), r1.at(i+1));
		for(int j=0; j<r2.size(); j++)
			std::cout << "+" << r2.at(j).toString() << std::endl;
		if(cost(std::vector<CoordInt>(r1.begin()+i, r1.begin()+i+1)) > cost(r2)) {
			for(unsigned int j=0; j<r2.size(); j++)
				r.push_back(r2.at(j));
		}
		else
			r.push_back(r1.at(i));

	}
	r.push_back(r1.at(r1.size()-1));
	return r;*/
	std::vector<CoordInt> r = checkDirection(path);
	if(r.size() == 0)
		r.push_back(goal);
	return r;
}

float PathFinding::cost(std::vector<CoordInt> path) {
	int cost = 0;
	for(unsigned int i=0; i<path.size()-1; i++) {
		if(path.at(i).x == path.at(i+1).x && path.at(i).y < path.at(i+1).y)
			cost += path.at(i+1).y-path.at(i).y;
		if(path.at(i).x < path.at(i+1).x && path.at(i).y < path.at(i+1).y)
			cost +=	DIAG_COST*((path.at(i+1).x-path.at(i).x)+(path.at(i+1).y-path.at(i).y));
		if(path.at(i).x < path.at(i+1).x && path.at(i).y == path.at(i+1).y)
			cost += path.at(i+1).x - path.at(i).x;
		if(path.at(i).x < path.at(i+1).x && path.at(i).y > path.at(i+1).y)
			cost +=	DIAG_COST*((path.at(i+1).x-path.at(i).x)+(path.at(i).y-path.at(i+1).y));
		if(path.at(i).x == path.at(i+1).x && path.at(i).y > path.at(i+1).y)
			cost += path.at(i).y - path.at(i+1).y;
		if(path.at(i).x > path.at(i+1).x && path.at(i).y > path.at(i+1).y)
			cost +=	DIAG_COST*((path.at(i).x-path.at(i+1).x)+(path.at(i).y-path.at(i+1).y));
		if(path.at(i).x > path.at(i+1).x && path.at(i).y == path.at(i+1).y)
			cost += path.at(i).x - path.at(i+1).x;
		if(path.at(i).x > path.at(i+1).x && path.at(i).y < path.at(i+1).y)
			cost +=	DIAG_COST*((path.at(i).x-path.at(i+1).x)+(path.at(i+1).y-path.at(i).y));
	}

	return cost;
}

std::vector<CoordInt> PathFinding::checkDirection(std::vector<CoordInt> path) {
	std::vector<CoordInt> r;
	int lastDir = D_NONE;
	for(int i=0; i<(int)path.size()-1; i++) {
		int currDir = D_NONE;
		if(path.at(i).x == path.at(i+1).x && path.at(i).y < path.at(i+1).y)
			currDir = D_NORTH;
		if(path.at(i).x < path.at(i+1).x && path.at(i).y < path.at(i+1).y)
			currDir = D_NORTHEAST;
		if(path.at(i).x < path.at(i+1).x && path.at(i).y == path.at(i+1).y)
			currDir = D_EAST;
		if(path.at(i).x < path.at(i+1).x && path.at(i).y > path.at(i+1).y)
			currDir = D_SOUTHEAST;
		if(path.at(i).x == path.at(i+1).x && path.at(i).y > path.at(i+1).y)
			currDir = D_SOUTH;
		if(path.at(i).x > path.at(i+1).x && path.at(i).y > path.at(i+1).y)
			currDir = D_SOUTHWEST;
		if(path.at(i).x > path.at(i+1).x && path.at(i).y == path.at(i+1).y)
			currDir = D_WEST;
		if(path.at(i).x > path.at(i+1).x && path.at(i).y < path.at(i+1).y)
			currDir = D_NORTHWEST;
		if(currDir != lastDir)
			r.push_back(path.at(i));
		lastDir = currDir;
	}
	return r;
}

void PathFinding::printPath(std::vector<CoordInt> path) {
	for(int i=0; i<15; i++) {
		for(int j=0; j<15; j++) {
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

} /* namespace util */
