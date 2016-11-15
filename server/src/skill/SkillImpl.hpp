/*
 * SkillImpl.hpp
 *
 *  Created on: 27 mai 2013
 *      Author: pierre
 */

#ifndef SKILLIMPL_HPP_
#define SKILLIMPL_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <map>

#include "../client/Player.hpp"
#include "../log/Log.hpp"
#include "../util/Util.hpp"

class SkillImpl {

public:
	static void process(int id, Player* player);

	void skill1(Player* player);
	void skill2(Player* player);
	void skill3(Player* player);
	void skill4(Player* player);
	void skill5(Player* player);
	void skill6(Player* player);
	void skill7(Player* player);
	void skill8(Player* player);
	void skill9(Player* player);
	void skill10(Player* player);
	void skill11(Player* player);

private:
	SkillImpl();
	static SkillImpl* getInstance();
	static boost::shared_ptr<SkillImpl> m_instance;
	std::map<int, boost::function<void(Player*)> > m_skills;
};


#endif /* SKILLIMPL_HPP_ */
