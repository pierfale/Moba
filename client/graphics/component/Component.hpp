/*
 * Component.hpp
 *
 *  Created on: 6 avr. 2013
 *      Author: pierre
 */

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <string>
#include <SFML/Graphics.hpp>

#include "../../util/Util.hpp"
#include "Window.hpp"
#include "../../ThreadManager.hpp"

//Log
#include "../../log/Log.hpp"
//Debug
#include "../../debug/Alloc.hpp"

namespace graphics {

	class Component {

	public:
		Component();
		Component(util::CoordInt coord, int width, int height);
		virtual ~Component();

		void setParent(Component* parent);
		virtual void setWindow(Window* window);
		void setCoord(util::CoordInt coord);
		void setSize(int width, int height);
		virtual void setSelected(bool state, bool force = false);
		virtual void setMinimalSize();
		void setVisible(bool state);
		void setEnable(bool state);
		void setWidthCenter();
		void setHeightCenter();
		void setAbsolute(bool state);

		virtual util::CoordInt getCoord();
		virtual util::CoordInt getRealCoord();
		virtual int getHeight();
		virtual int getWidth();
		virtual std::string getComponentName();

		virtual bool isSelectable();
		virtual bool isContainer();
		bool isSelected();
		bool isAbsolute();

		virtual void draw(sf::RenderWindow* render) = 0;
		virtual bool event(sf::Event* event, bool used) = 0;
		virtual void validate();
		virtual std::string toString(bool recursive = false);

	protected:
		Window* getWindow();
		Component* getParent();
		util::CoordInt m_coord;
		int m_width;
		int m_height;
		Component* m_parent;
		Window* m_window;

		bool m_focus;
		bool m_pressed;
		bool m_selected;
		bool m_visible;
		bool m_enable;
		bool m_absolute;

		bool m_widthCenter;
		bool m_heightCenter;

	};
}


#endif /* COMPONENT_HPP_ */
