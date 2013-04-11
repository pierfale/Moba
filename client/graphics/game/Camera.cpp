/*
 * Camera.cpp
 *
 *  Created on: 9 avr. 2013
 *      Author: Béni
 */

#include "Camera.h"

namespace graphics {

	Camera::Camera() : m_coord(0,0), m_lmW(0), m_lmH(0) {}
	Camera::Camera(int x, int y) : m_coord(x,y) , m_lmW(0), m_lmH(0) {}
	Camera::Camera(util::Coordinates &copy) : m_coord(copy), m_lmW(0), m_lmH(0) {}
	Camera::~Camera() {}

	util::Coordinates Camera::getCoord() { return m_coord; }

	void Camera::setLandMark(int w, int h) {
		m_lmW = w; m_lmH = w;
	}

	void Camera::event(sf::Event* event, int* gbW, int* gbH) {
		if (event->type == sf::Event::KeyPressed) {
			if (event->key.code == sf::Keyboard::Right) {
				if (m_coord.x+((*gbW)/50) < m_lmW ) ++m_coord.x;
			}
			if (event->key.code == sf::Keyboard::Left) {
				if (m_coord.x > 0 ) --m_coord.x;
			}
			if (event->key.code == sf::Keyboard::Up) {
				if (m_coord.y > 0 ) --m_coord.y;
			}
			if (event->key.code == sf::Keyboard::Down) {
				if (m_coord.y+((*gbH)/50) < m_lmH ) m_coord.y++;
			}
		}
	}

} /* namespace graphics */
