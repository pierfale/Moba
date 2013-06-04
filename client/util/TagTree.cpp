/*
 * TagTree.cpp
 *
 *  Created on: 26 mai 2013
 *      Author: pierre
 */

#include "TagTree.hpp"

namespace util {

	TagTree::TagTree(graphics::StringStyle* style) : m_style(style) {
		if(m_style == NULL)
			m_style = new graphics::StringStyle();
	}

	void TagTree::addChild(TagTree* child) {
		m_child.push_back(child);
	}

	void TagTree::setContents(std::string contents) {
		m_contents = contents;
	}

	void TagTree::display(int n) {
		for(int i=0; i<n; i++)
			std::cout << "   ";
		std::cout << m_contents << std::endl;

		for(unsigned int i=0; i<m_child.size(); i++)
			m_child.at(i).display(n+1);
	}

	graphics::StringStyle* TagTree::getStyle() {
		return m_style;
	}

	std::string TagTree::getContents() {
		return m_contents;
	}

	int TagTree::getChildSize() {
		return m_child.size();
	}

	TagTree* TagTree::getChild(int i) {
		return &m_child.at(i);
	}
}


