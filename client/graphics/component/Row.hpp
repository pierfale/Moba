/*
 * Row.hpp
 *
 *  Created on: 16 avr. 2013
 *      Author: pierre
 */

#ifndef ROW_HPP_
#define ROW_HPP_

#include "Component.hpp"
#include "../listener/TableListener.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class Table;

	class Row {

	public:
		Row(Table* table);
		~Row();
		void setSize(int width, int height);
		void setCoord(util::CoordInt coord);
		void setWindow(Window* window);
		void setSelect(bool state);

		bool set(int i, Component* componant);
		Component* get(int i);
		bool isFocus();
		bool isSelected();
		void validate();
		bool event(sf::Event* event, bool used);
		void draw(sf::RenderWindow render);

	private:
		Table* m_table;
		Window* m_window;
		boost::ptr_vector<Component> m_components;
		int m_width;
		int m_height;
		util::CoordInt m_coord;

		bool m_focus;
		bool m_selected;
	};

}




#endif /* ROW_HPP_ */
