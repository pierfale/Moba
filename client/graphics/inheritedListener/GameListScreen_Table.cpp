/*
 * GameListScreen_Table.cpp
 *
 *  Created on: 18 avr. 2013
 *      Author: pierre
 */

#include "GameListScreen_Table.hpp"

namespace graphics {

	GameListScreen_Table::GameListScreen_Table(GameListScreen* view) : m_view(view) {

	}

	void GameListScreen_Table::rowSelected(void* origin) {
		m_view->gameChanged(origin);
	}
}



