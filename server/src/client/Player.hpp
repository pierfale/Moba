/*
 * Player.hpp
 *
 *  Created on: 22 avr. 2013
 *      Author: pierre
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <boost/timer.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <map>
#include <utility>
#include <string>
#include <cfloat>
#include "PlayerStat.hpp"
#include "../util/Util.hpp"
#include "Packet.hpp"
#include "PacketType.hpp"
#include "../skill/Skill.hpp"
#include "../database/Database.hpp"

#define PLAYER_STOP_SPELL_TIME 0.2
#define CHARACTER_DIAG_RATIO 0.7

#define PLAYER_STATE_NONE 0
#define PLAYER_STATE_MOVETO 1
#define PLAYER_STATE_TARGET 2

class Player {

public:
	Player(int id, Client* client, std::string name, int level, int exp);
	~Player();
	int getID();
	std::string getName();
	int getLevel();
	int getExp();
	void incExp(int value);
	network::PacketType::PacketContents getTeam();
	util::CoordFloat getCoord();
	void setCoord(util::CoordFloat coord);
	int getDirection();
	void setDirection(int direction);
	PlayerStat* getStat();
	void setLastTarget(Player* p);
	void setTarget(Player* p);
	Player* getLastTarget();
	Player* getTarget();
	void setAlive(bool state);
	bool isAlive();
	Client* getClient();
	void sendMessage(std::string message);

	void setTeam(network::PacketType::PacketContents team);
	float getCooldown(int spell);
	void resetCooldown(int spell);
	void checkAutoAttack();
	void updateCoord();
	void clearGoal();
	void addGoal(util::CoordInt coord);
	void setState(int state);
	void updateStat();
	void addSpell(int id);
	bool hasSpell(int id);
	int spellSize();
	int getSpell(int i);

	void addSkill(Skill* skill);
	int skillSize();
	Skill* getSkill(int i);

	void setPhysicalDamage(int n, Player* origin);
	void setMagicalDamage(int n, Player* origin);

private:
	int m_id;
	Client* m_client;
	std::string m_name;
	int m_level;
	int m_exp;
	network::PacketType::PacketContents m_team;
	util::CoordFloat m_coord;
	int m_direction;
	PlayerStat m_stat;
	Player* m_target;
	int m_state;
	std::map<int, boost::timer> m_cooldowns;
	boost::timer m_lastAttack;
	bool m_lastAttackFirst;
	boost::timer m_timer;
	bool m_alive;
	std::vector<util::CoordFloat> m_goal;
	boost::ptr_vector<Skill> m_skills;
	std::vector<int> m_spells;

};

#endif

