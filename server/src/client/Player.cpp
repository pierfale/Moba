/*
 * Player.cpp
 *
 *  Created on: 22 avr. 2013
 *      Author: pierre
 */

#include "Player.hpp"
#include "../spell/SingleTargetSpell.hpp"
#include "../skill/SkillImpl.hpp"
#include "Client.hpp"
#include "../game/Game.hpp"

	Player::Player(int id, Client* client, std::string name, int level, int exp) : m_id(id), m_name(name), m_level(level), m_exp(exp),  m_direction(0), m_stat(client) {
		m_state = PLAYER_STATE_NONE;
		m_target = NULL;
		m_team = network::PacketType::FACTION_TEAM1;
		m_client = client;
		m_lastAttackFirst = false;
		m_alive = true;
	}

	Player::~Player() {
		while(m_skills.size() > 0)
			m_skills.release(m_skills.begin()).release();
	}

	int Player::getID() {
		return m_id;
	}

	std::string Player::getName() {
		return m_name;
	}

	int Player::getLevel() {
		return m_level;
	}

	int Player::getExp() {
		return m_exp;
	}

	void Player::incExp(int value) {
		m_exp += value;

		if (m_exp >= (m_level*5)+10) {
			m_exp = m_exp-(m_level*5)+10;
			m_level++;

			Database::update("UPDATE characters SET Characters_Level ='"+
					util::Cast::intToString(m_level)+"' WHERE Characters_ID='"+
					util::Cast::intToString(m_id)+"'");

		}
	}

	network::PacketType::PacketContents Player::getTeam() {
		return m_team;
	}

	void Player::setTeam(network::PacketType::PacketContents team) {
		m_team = team;
	}

	util::CoordFloat Player::getCoord() {
		return m_coord;
	}

	PlayerStat* Player::getStat() {
		return &m_stat;
	}

	void Player::setCoord(util::CoordFloat coord) {
		m_coord = coord;
	}

	int Player::getDirection() {
		return m_direction;
	}

	void Player::setDirection(int direction) {
		m_direction = direction;
	}

	float Player::getCooldown(int spell) {
		if(m_cooldowns.find(spell) == m_cooldowns.end())
			return FLT_MAX;
		else
		return m_cooldowns[spell].elapsed();
	}

	void Player::resetCooldown(int spell) {
		if(m_cooldowns.find(spell) == m_cooldowns.end())
			m_cooldowns.insert(std::pair<int, boost::timer>(spell, boost::timer()));
		else
			m_cooldowns[spell].restart();
		m_lastAttack.restart();
		m_lastAttackFirst = true;
		network::Packet packet(NULL, network::PacketType::GAME_PLAYERMOVE);
		packet << m_id << m_coord.x << m_coord.y << network::PacketType::DIRECTION_NONE;
		m_client->getGame()->sendAll(packet);
	}

	void Player::setTarget(Player* p) {
		m_target = p;
		network::Packet packet(m_client->getSocket(), network::PacketType::GAME_ANSWERTARGET);
		if(p == NULL)
			packet << 0;
		else
			packet << p->getID();
		packet.send();
	}

	Player* Player::getTarget() {
		return m_target;
	}

	void Player::setState(int state) {
		m_state = state;
	}

	void Player::setAlive(bool state) {
		m_alive = state;
	}

	bool Player::isAlive() {
		return m_alive;
	}

	void Player::addGoal(util::CoordInt coord) {
		m_goal.push_back(util::CoordFloat(coord.x, coord.y));
	}

	void Player::clearGoal() {
		m_goal.clear();
	}

	void Player::addSkill(Skill* skill) {
		m_skills.push_back(skill);
	}

	void Player::checkAutoAttack() {
		if(m_target != NULL && m_target->isAlive() && m_state != PLAYER_STATE_MOVETO) {
			if(util::Math::distance(this->getCoord(), m_target->getCoord()) < this->getStat()->range()-2) {
				if(SingleTargetSpell::process(1, this, m_target)) {
					if(m_target->getTarget() == NULL) {
						m_target->setTarget(this);
						m_target->checkAutoAttack();
						m_target->setState(PLAYER_STATE_TARGET);
					}
					if(m_state == PLAYER_STATE_TARGET)
						m_goal.clear();
					network::Packet answer(NULL, network::PacketType::GAME_PLAYERLAUNCHSINGLETARGETSPELL);
					int idSpell = m_stat.range() >= 200 ? 2 : 1;
					answer << idSpell << m_id << m_target->getID();
					m_client->getGame()->sendAll(answer);
				}
			}
			else {
				if(m_goal.size() == 0) {
					//TODO pathfinding
					m_goal.push_back(m_target->getCoord());
				}
			}
		}
		//TODO else check the nearest target
	}

	void Player::updateCoord() {
		float elapsed = m_timer.elapsed();
		m_timer.restart();
		if(m_lastAttack.elapsed() < PLAYER_STOP_SPELL_TIME)
			return;
		else if(m_lastAttackFirst) {
			if(m_goal.size() > 0) {
				network::Packet packet(NULL, network::PacketType::GAME_PLAYERMOVE);
				packet << m_id << m_coord.x << m_coord.y << m_direction;
				m_client->getGame()->sendAll(packet);
			}
			m_lastAttackFirst = false;
		}

		//checkDirection
		if(m_goal.size() == 0)
			return;

		network::PacketType::PacketContents direction;

		if(m_goal.at(0).x == m_coord.x && m_goal.at(0).y == m_coord.y) {
			direction = network::PacketType::DIRECTION_NONE;
			m_goal.erase(m_goal.begin());

		}
		if(m_goal.size() > 0) {
			if(m_goal.at(0).x == m_coord.x) {
				if(m_goal.at(0).y < m_coord.y)
					direction = network::PacketType::DIRECTION_NORTH;
				else if(m_goal.at(0).y > m_coord.y)
					direction = network::PacketType::DIRECTION_SOUTH;
			}
			else if(m_goal.at(0).x < m_coord.x) {
				if(m_goal.at(0).y < m_coord.y)
					direction = network::PacketType::DIRECTION_NORTHWEST;
				else if(m_goal.at(0).y > m_coord.y)
					direction = network::PacketType::DIRECTION_SOUTHWEST;
				else
					direction = network::PacketType::DIRECTION_WEST;
			}
			else {
				if(m_goal.at(0).y < m_coord.y)
					direction = network::PacketType::DIRECTION_NORTHEAST;
				else if(m_goal.at(0).y > m_coord.y)
					direction = network::PacketType::DIRECTION_SOUTHEAST;
				else
					direction = network::PacketType::DIRECTION_EAST;
			}

			int diffX = m_goal.at(0).x > m_coord.x ? m_goal.at(0).x - m_coord.x : m_coord.x - m_goal.at(0).x;
			int diffY = m_goal.at(0).y > m_coord.y ? m_goal.at(0).y - m_coord.y : m_coord.y - m_goal.at(0).y;

			if(direction == network::PacketType::DIRECTION_NORTH)
				m_coord.y = m_stat.movementSpeed()*elapsed < diffY ? m_coord.y - m_stat.movementSpeed()*elapsed : m_goal.at(0).y;
			if(direction == network::PacketType::DIRECTION_SOUTH)
				m_coord.y = m_stat.movementSpeed()*elapsed < diffY ? m_coord.y + m_stat.movementSpeed()*elapsed : m_goal.at(0).y;
			if(direction == network::PacketType::DIRECTION_EAST)
				m_coord.x = m_stat.movementSpeed()*elapsed < diffX ? m_coord.x + m_stat.movementSpeed()*elapsed : m_goal.at(0).x;
			if(direction == network::PacketType::DIRECTION_WEST)
				m_coord.x = m_stat.movementSpeed()*elapsed < diffX ? m_coord.x - m_stat.movementSpeed()*elapsed : m_goal.at(0).x;
			if(direction == network::PacketType::DIRECTION_NORTHEAST) {
				m_coord.x = CHARACTER_DIAG_RATIO*m_stat.movementSpeed()*elapsed < diffX ?  m_coord.x+CHARACTER_DIAG_RATIO*m_stat.movementSpeed()*elapsed : m_goal.at(0).x;
				m_coord.y = CHARACTER_DIAG_RATIO*m_stat.movementSpeed()*elapsed < diffY ?  m_coord.y-CHARACTER_DIAG_RATIO*m_stat.movementSpeed()*elapsed : m_goal.at(0).y;
			}
			if(direction == network::PacketType::DIRECTION_NORTHWEST) {
				m_coord.x = CHARACTER_DIAG_RATIO*m_stat.movementSpeed()*elapsed < diffX ?  m_coord.x-CHARACTER_DIAG_RATIO*m_stat.movementSpeed()*elapsed : m_goal.at(0).x;
				m_coord.y = CHARACTER_DIAG_RATIO*m_stat.movementSpeed()*elapsed < diffY ?  m_coord.y-CHARACTER_DIAG_RATIO*m_stat.movementSpeed()*elapsed : m_goal.at(0).y;
			}
			if(direction == network::PacketType::DIRECTION_SOUTHEAST) {
				m_coord.x = CHARACTER_DIAG_RATIO*m_stat.movementSpeed()*elapsed < diffX ?  m_coord.x+CHARACTER_DIAG_RATIO*m_stat.movementSpeed()*elapsed : m_goal.at(0).x;
				m_coord.y = CHARACTER_DIAG_RATIO*m_stat.movementSpeed()*elapsed < diffY ?  m_coord.y+CHARACTER_DIAG_RATIO*m_stat.movementSpeed()*elapsed : m_goal.at(0).y;
			}
			if(direction == network::PacketType::DIRECTION_SOUTHWEST) {
				m_coord.x = CHARACTER_DIAG_RATIO*m_stat.movementSpeed()*elapsed < diffX ?  m_coord.x-CHARACTER_DIAG_RATIO*m_stat.movementSpeed()*elapsed : m_goal.at(0).x;
				m_coord.y = CHARACTER_DIAG_RATIO*m_stat.movementSpeed()*elapsed < diffY ?  m_coord.y+CHARACTER_DIAG_RATIO*m_stat.movementSpeed()*elapsed : m_goal.at(0).y;
			}
		}
		else
			m_state = PLAYER_STATE_NONE;

 		if(direction != m_direction) {
			network::Packet packet(NULL, network::PacketType::GAME_PLAYERMOVE);
			packet << m_id << m_coord.x << m_coord.y << direction;
			m_client->getGame()->sendAll(packet);
			m_direction = direction;
		}

	}

	void Player::updateStat() {
		m_stat.reset();
		m_spells.clear();
		//skills
		for(unsigned int i=0; i<m_skills.size(); i++)
			SkillImpl::process(m_skills.at(i).getId(), this);

	}

	void Player::addSpell(int id) {
		for(unsigned int i=0; i<m_spells.size(); i++) {
			if(m_spells.at(i) == id)
				return;
		}
		m_spells.push_back(id);
	}

	bool Player::hasSpell(int id) {
		if(id == 1)
			return true;
		for(unsigned int i=0; i<m_spells.size(); i++) {
			if(m_spells.at(i) == id)
				return true;
		}
		return false;
	}

	int Player::spellSize() {
		return m_spells.size();
	}

	int Player::getSpell(int i) {
		return m_spells.at(i);
	}

	int Player::skillSize() {
		return m_skills.size();
	}

	Skill* Player::getSkill(int i) {
		return &m_skills.at(i);
	}

	void Player::setPhysicalDamage(int n, Player* origin) {
		if(n > m_stat.physicalArmor()) {
			m_stat.changeLife(-n+m_stat.physicalArmor());

			network::Packet packet(origin->getClient()->getSocket(), network::PacketType::GAME_DOPHYSICALDAMAGE);
			packet << (n-m_stat.physicalArmor()) << m_id;
			packet.send();

			if(m_stat.life() == 0) {
				m_client->getCharacter()->setAlive(false);
				m_client->getCharacter()->setState(PLAYER_STATE_NONE);
				m_client->getGame()->getMode()->dead(m_client, origin);
			}
		}
	}

	void Player::setMagicalDamage(int n, Player* origin) {
		if(n > m_stat.magicalArmor()) {
			m_stat.changeLife(-n+m_stat.magicalArmor());

			network::Packet packet(origin->getClient()->getSocket(), network::PacketType::GAME_DOMAGICALDAMAGE);
			packet << (n-m_stat.physicalArmor()) << m_id;
			packet.send();

			if(m_stat.life() == 0) {
				m_client->getCharacter()->setAlive(false);
				m_client->getCharacter()->setState(PLAYER_STATE_NONE);
				m_client->getGame()->getMode()->dead(m_client, origin);
			}
		}
	}

	Client* Player::getClient() {
		return m_client;
	}

	void Player::sendMessage(std::string message) {
		network::Packet answer(m_client->getSocket(), network::PacketType::GAME_SETMESSAGE);
		answer << message;
		answer.send();
	}

