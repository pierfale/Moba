/*
 * GameMode.hpp
 *
 *  Created on: 12 mai 2013
 *      Author: pierre
 */

#ifndef GAMEMODE_HPP_
#define GAMEMODE_HPP_

namespace graphics {

	class GameMode {

	public:
		static network::PacketType::PacketTypeFinal getType();
		Component* getComponent1();
	};
}


#endif /* GAMEMODE_HPP_ */
