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
#include "../log/Log.hpp"

namespace graphics {

	class GUIStyle {

	public:
		static void init();
		static BasicStyle* button();
		static BasicStyle* label();
		static BasicStyle* textfield();
		static WindowStyle* innerwindow();

	private:
		GUIStyle();
		static GUIStyle* getInstance();
		static GUIStyle* m_instance;

		BasicStyle* m_button;
		BasicStyle* m_label;
		BasicStyle* m_textfield;
		WindowStyle* m_innerwindow;
	};
}


#endif /* GUISTYLE_HPP_ */
