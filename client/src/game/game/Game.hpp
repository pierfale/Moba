/*
 * Game.hpp
 *
 *  Created on: 18 avr. 2013
 *      Author: pierre
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <string>

namespace game {

	class Game {

	public:
		Game(int id, std::string name, std::string creator, int nPlayer);
		int getID();
		std::string getName();
		std::string getCreator();
		int getNPlayer();
		void setNPlayer(int n);

	private:
		int m_id;
		int m_nPlayer;
		std::string m_name;
		std::string m_creator;
	};
}


#endif /* GAME_HPP_ */
