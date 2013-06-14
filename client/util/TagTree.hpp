/*
 * TagTree.hpp
 *
 *  Created on: 26 mai 2013
 *      Author: pierre
 */

#ifndef TAGTREE_HPP_
#define TAGTREE_HPP_

#include <boost/ptr_container/ptr_vector.hpp>
#include "../graphics/style/StringStyle.hpp"

namespace util {

	class TagTree {

	public:
		TagTree(graphics::StringStyle* style = NULL);
		void setContents(std::string contents);
		void addChild(TagTree* child);
		void display(int n);
		graphics::StringStyle* getStyle();
		std::string getContents();
		int getChildSize();
		TagTree* getChild(int i);

	private:
		boost::ptr_vector<TagTree> m_child;
		std::string m_contents;
		graphics::StringStyle* m_style;


	};
}


#endif /* TAGTREE_HPP_ */
