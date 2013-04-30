/*
 * Table.cpp
 *
 *  Created on: 16 avr. 2013
 *      Author: pierre
 */

#include "Table.hpp"

namespace graphics {

	Table::Table(TableStyle* style) : m_style(style), m_nextId(1) {

	}

	Table::Table(std::vector<std::string> columns, TableStyle* style) : m_style(style), m_nextId(1)  {
		setColumns(columns);
	}

	Table::~Table() {
		for(std::map<int,Row*>::const_iterator it = m_rows.begin(); it != m_rows.end(); ++it){
			delete &(*it->second);
		}
	}

	void Table::setColumns(std::vector<std::string> columns) {
		m_columns = columns;
		m_columnsWidth.clear();
		for(unsigned int i=0; i<m_columns.size(); i++) {
			m_columnsWidth.push_back(0);
			Label lbl(m_columns.at(i), GUIStyle::label());
			lbl.setAlign(Label::alignCenter);
			lbl.setParent(this);
			m_columnsLabel.push_back(lbl);
		}
	}

	void Table::setColumnsWidth(unsigned int i, unsigned int width) {
		if(i >= 0 && i < m_columnsWidth.size())
			m_columnsWidth.at(i) = width;
	}

	int Table::addRow() {
		int id = m_nextId++;
		m_rows[id] = new Row(this);
		return id;
	}

	void Table::removeAllRow() {
		while(m_rows.size() > 0) {
			delete m_rows.begin()->second;
			m_rows.erase(m_rows.begin());
			m_rowsValue.erase(m_rowsValue.begin());
		}
	}

	bool Table::set(int row, int column, Component* component) {
		if(m_rows.find(row) != m_rows.end()) {
			return m_rows[row]->set(column, component);
		}
		return false;
	}

	void Table::setValueOnRow(int id, void* value) {
		m_rowsValue[id] = value;
	}

	int Table::rowCount() {
		return m_rows.size();
	}

	int Table::columnCount() {
		return m_columns.size();
	}

	int Table::getSelectedRow() {
		for(std::map<int,Row*>::const_iterator it = m_rows.begin(); it != m_rows.end(); ++it){
			if(it->second->isSelected())
					return it->first;
		}
		return 0;
	}

	void* Table::getValueOnRow(int id) {
		if(m_rowsValue.find(id) != m_rowsValue.end()) {
			return m_rowsValue[id];
		}
		return NULL;
	}

	void Table::addListener(TableListener* listener) {
		m_listener.push_back(listener);
	}

	boost::ptr_vector<TableListener>* Table::getListeners() {
		return &m_listener;
	}

	void Table::setSelect(Row* row) {
		for(std::map<int,Row*>::const_iterator it = m_rows.begin(); it != m_rows.end(); ++it) {
			it->second->setSelect(false);
		}
		row->setSelect(true);
	}

	void Table::validate() {
		int nUndefinedSize = 0;
		int definedSize = 1+m_columnsWidth.size();
		for(unsigned int i=0; i<m_columnsWidth.size(); i++) {
			if(m_columnsWidth.at(i) == 0)
				nUndefinedSize++;
			else
				definedSize += m_columnsWidth.at(i);
		}
		int x = 0;
		for(unsigned int i=0; i<m_columns.size(); i++) {
			x++;
			if(m_columnsWidth.at(i) == 0)
				m_columnsLabel.at(i).setSize((m_width-definedSize)/nUndefinedSize, 40);
			else
				m_columnsLabel.at(i).setSize(m_columnsWidth.at(i), 40);

			m_columnsLabel.at(i).setCoord(util::CoordInt(x, 0));
			if(m_columnsWidth.at(i) == 0)
				x += (m_width-definedSize)/nUndefinedSize;
			else
				x+= m_columnsWidth.at(i);
		}
		int y = 40;
		for(std::map<int,Row*>::const_iterator it = m_rows.begin(); it != m_rows.end(); ++it){
			it->second->setSize(m_width, 40);
			it->second->setCoord(util::CoordInt(0, y));
			it->second->setWindow(m_window);
			x = 0;
			for(unsigned int j=0; j<m_columns.size(); j++) {
				x++;
				if(m_columnsWidth.at(j) == 0)
					it->second->get(j)->setSize((m_width-definedSize)/nUndefinedSize, 40);
				else
					it->second->get(j)->setSize(m_columnsWidth.at(j), 40);

				it->second->get(j)->setCoord(util::CoordInt(x, y));
				if(m_columnsWidth.at(j) == 0)
					x += (m_width-definedSize)/nUndefinedSize;
				else
					x+= m_columnsWidth.at(j);
			}
			y += 40;
		}

	}

	bool Table::event(sf::Event* event, bool used) {
		if(m_style == NULL || !m_visible)
			return used;
		for(std::map<int,Row*>::const_iterator it = m_rows.begin(); it != m_rows.end(); ++it){
			used = it->second->event(event, used);
		}
		return used;
	}

	void Table::draw(sf::RenderWindow* render) {
		if(m_style == NULL) {
			log_err "No style has been applied to the component "+getComponentName() end_log_err;
			return;
		}
		if(!m_visible)
			return;
		util::CoordInt coord = getRealCoord();
		BasicStyle* headerStyle = new BasicStyle();
		headerStyle->setFontColor(m_style->headerTextColor());
		for(unsigned int i=0; i<m_columnsLabel.size(); i++) {
			sf::RectangleShape rect(sf::Vector2f(m_columnsLabel.at(i).getWidth(), m_columnsLabel.at(i).getHeight()));
			rect.setPosition(coord.x+m_columnsLabel.at(i).getCoord().x, coord.y+m_columnsLabel.at(i).getCoord().y);
			rect.setOutlineThickness(m_style->borderSize());
			rect.setOutlineColor(m_style->borderColor());
			rect.setFillColor(m_style->headerBackgroundColor());
			render->draw(rect);
			m_columnsLabel.at(i).setStyle(headerStyle);
			m_columnsLabel.at(i).draw(render);
		}
		delete headerStyle;
		for(std::map<int,Row*>::const_iterator it = m_rows.begin(); it != m_rows.end(); ++it){
			for(unsigned int j=0; j<m_columns.size(); j++) {
				sf::RectangleShape rect(sf::Vector2f(it->second->get(j)->getWidth(), it->second->get(j)->getHeight()));
				rect.setPosition(coord.x+it->second->get(j)->getCoord().x, coord.y+it->second->get(j)->getCoord().y);
				rect.setOutlineThickness(m_style->borderSize());
				rect.setOutlineColor(m_style->borderColor());
				if(it->second->isSelected())
					rect.setFillColor(m_style->backgroundColorSelect());
				else if(it->second->isFocus())
					rect.setFillColor(m_style->backgroundColorFocus());
				else
					rect.setFillColor(m_style->backgroundColor());
				render->draw(rect);
				it->second->get(j)->draw(render);
			}
		}

	}

}


