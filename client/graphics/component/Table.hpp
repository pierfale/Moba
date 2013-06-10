/*
 * Table.hpp
 *
 *  Created on: 16 avr. 2013
 *      Author: pierre
 */

#ifndef TABLE_HPP_
#define TABLE_HPP_

#include <string>
#include <map>

#include "Component.hpp"
#include "Label.hpp"
#include "Row.hpp"
#include "../listener/TableListener.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class Table : public Component {

	public:
		Table(TableStyle* style=NULL);
		Table(std::vector<std::string> columns, TableStyle* style=NULL);
		~Table();
		void setColumns(std::vector<std::string> columns);
		void setColumnsWidth(unsigned int i, unsigned int width);
		int addRow();
		void removeAllRow();
		bool set(int row, int column, Component* component);
		void setValueOnRow(int id, void* value);
		void* getValueOnRow(int id);
		void setSelect(Row* row);
		Component* get(int row, int column);
		int getSelectedRow();
		void addListener(TableListener* listener);
		boost::ptr_vector<TableListener>* getListeners();

		int rowCount();
		int columnCount();



		void validate();
		bool event(sf::Event* event, bool used);
		void draw(sf::RenderWindow* render);

	private:
		TableStyle* m_style;
		std::vector<std::string> m_columns;
		std::vector<Label> m_columnsLabel;
		std::vector<int> m_columnsWidth;
		std::map<int,Row*> m_rows;
		std::map<int,void*> m_rowsValue;
		int m_nextId;
		boost::ptr_vector<TableListener> m_listener;
	};
}

#endif /* TABLE_HPP_ */
