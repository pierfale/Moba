/*
 * Camera.h
 *
 *  Created on: 9 avr. 2013
 *      Author: Béni
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <iostream>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <boost/timer.hpp>

#include "../../util/Coordinates.hpp"
#include "../ImageLoader.hpp"

namespace graphics {

	class Camera {
	public:
		Camera();
		Camera(int x, int y);
		Camera(util::CoordInt &copy);
		virtual ~Camera();

		void setLandMark(int w, int h);

		util::CoordInt getCoord();
		void setCoord(util::CoordInt coord);

		bool event(sf::Event* event, bool used, int* w, int* h);
		void validate(int* gbW, int* gbH);

	private:
		int m_rate;
		util::CoordInt m_coord;
		int m_lmW, m_lmH;
		boost::timer m_frame;
	};

} /* namespace graphics */
#endif /* CAMERA_H_ */
