/*
 * GUIStyle.hpp
 *
 *  Created on: 9 avr. 2013
 *      Author: pierre
 */

#ifndef GUISTYLE_HPP_
#define GUISTYLE_HPP_

#include <string>

#include "style/StyleInclude.hpp"

//Log
#include "../log/Log.hpp"
//Debug
#include "../debug/Alloc.hpp"

namespace graphics {

	class GUIStyle {

	public:
		~GUIStyle();
		static void init();
		static BasicStyle* button();
		static BasicStyle* label();
		static BasicStyle* textfield();
		static WindowStyle* innerwindow();
		static LineStyle* line();
		static TableStyle* table();
		static BasicStyle* characterFrame();
		static BasicStyle* buttonImage();
		static ScrollBarStyle* scrollbar();

	private:
		GUIStyle();

		static GUIStyle* getInstance();
		static boost::shared_ptr<GUIStyle> m_instance;

		boost::shared_ptr<BasicStyle> m_button;
		boost::shared_ptr<BasicStyle> m_label;
		boost::shared_ptr<BasicStyle> m_textfield;
		boost::shared_ptr<WindowStyle> m_innerwindow;
		boost::shared_ptr<LineStyle> m_line;
		boost::shared_ptr<TableStyle> m_table;
		boost::shared_ptr<BasicStyle> m_characterFrame;
		boost::shared_ptr<BasicStyle> m_buttonImage;
		boost::shared_ptr<ScrollBarStyle> m_scrollbar;
	};
}


#endif /* GUISTYLE_HPP_ */
