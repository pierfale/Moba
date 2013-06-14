/*
 * GameListScreen_Table.hpp
 *
 *  Created on: 18 avr. 2013
 *      Author: pierre
 */

#ifndef GAMELISTSCREEN_TABLE_HPP_
#define GAMELISTSCREEN_TABLE_HPP_

#include "../listener/TableListener.hpp"
#include "../screen/GameListScreen.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class GameListScreen_Table : public TableListener {

	public:
		GameListScreen_Table(GameListScreen* view);
		void rowSelected(void* origin);

	private:
		GameListScreen* m_view;

	};
}

#endif /* GAMELISTSCREEN_TABLE_HPP_ */
