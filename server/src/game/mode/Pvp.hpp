/*
 * Pvp.hpp
 *
 *  Created on: 28 avr. 2013
 *      Author: pierre
 */

#ifndef PVP_HPP_
#define PVP_HPP_

#include "GameMode.hpp"
#include "../../database/Database.hpp"

class Pvp : public GameMode {

public:
	Pvp();
	void init();
	void start();
	bool run();
	void end();
	void dead(Client* client, Player* killer);
	void randomizeCoord();
	void expManage();

private:
	static util::CoordFloat m_team1Spawn;
	static util::CoordFloat m_team2Spawn;
	int m_scoreTeam1, m_scoreTeam2, m_id, m_expTeam1, m_expTeam2;
	float m_time;
	boost::timer m_timer;
};


#endif /* PVP_HPP_ */
