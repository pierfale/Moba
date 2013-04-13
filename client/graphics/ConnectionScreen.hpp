/*
 * ConnectionScreen.hpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#ifndef CONNECTIONSCREEN_HPP_
#define CONNECTIONSCREEN_HPP_

#include "component/Container.hpp"
#include "component/ComponentInclude.hpp"
#include "GUIStyle.hpp"
#include "layout/LayoutInclude.hpp"

#include "CharacterScreen.hpp"

namespace graphics {

	class ConnectionScreen : public Container {

	public:
		ConnectionScreen();
		void load();
		void startConnection();

	private:
		Button* m_bConnection;

	};

}


#endif /* CONNECTIONSCREEN_HPP_ */
