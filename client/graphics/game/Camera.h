/*
 * Camera.h
 *
 *  Created on: 9 avr. 2013
 *      Author: Béni
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <iostream>

#include "../../util/Coordinates.hpp"
#include "SFML/Window.hpp"


namespace graphics {

	class Camera {
	public:
		Camera();
		Camera(int x, int y);
		Camera(util::Coordinates &copy);
		virtual ~Camera();

		void setLandMark(int w, int h);

		util::Coordinates getCoord();
		void event(sf::Event* event, int* w, int* h);

	private:
		util::Coordinates m_coord;
		int m_lmW, m_lmH;
	};

} /* namespace graphics */
#endif /* CAMERA_H_ */
