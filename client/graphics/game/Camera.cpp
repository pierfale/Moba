/*
 * Camera.cpp
 *
 *  Created on: 9 avr. 2013
 *      Author: Béni
 */

#include "Camera.h"

namespace graphics {

	Camera::Camera() : m_rate(10), m_coord(0,0), m_lmW(0), m_lmH(0) {}
	Camera::Camera(int x, int y) : m_rate(10), m_coord(x,y) , m_lmW(0), m_lmH(0) {}
	Camera::Camera(util::CoordInt &copy) : m_rate(10),m_coord(copy), m_lmW(0), m_lmH(0) {}
	Camera::~Camera() {}

	util::CoordInt Camera::getCoord() { return m_coord; }

	void Camera::setLandMark(int w, int h) {
		m_lmW = w; m_lmH = w;
	}

	void Camera::setCoord(util::CoordInt coord) { m_coord = coord ;}

	bool Camera::event(sf::Event* event, bool used, int* gbW, int* gbH) {
		if (m_frame.elapsed() > 0.25) {
			m_frame.restart();
			m_rate+=5;
		}
		if (event->type == sf::Event::KeyPressed) {
			if (event->key.code == sf::Keyboard::Right) {
				if (m_coord.x+m_rate >= (m_lmW*50)-(*gbW) )
					m_coord.x = (m_lmW*50)-(*gbW)-1;
				else
					m_coord.x+=m_rate;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					if (m_coord.y+m_rate > (m_lmH*50)-(*gbH))
						m_coord.y = (m_lmH*50)-(*gbH);
					else
						m_coord.y+=m_rate;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					m_coord.y-=m_rate;
					if (m_coord.y < 0 ) m_coord.y = 0;
				}
			}
			if (event->key.code == sf::Keyboard::Left) {
				m_coord.x-=m_rate;
				if (m_coord.x < 0 ) m_coord.x = 0;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					if (m_coord.y+m_rate > (m_lmH*50)-(*gbH))
						m_coord.y = (m_lmH*50)-(*gbH);
					else
						m_coord.y+=m_rate;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					m_coord.y-=m_rate;
					if (m_coord.y < 0 ) m_coord.y = 0;
				}
			}
			if (event->key.code == sf::Keyboard::Up) {
				m_coord.y-=m_rate;
				if (m_coord.y < 0 ) m_coord.y = 0;
			}
			if (event->key.code == sf::Keyboard::Down) {
				if (m_coord.y+m_rate > (m_lmH*50)-(*gbH))
					m_coord.y = (m_lmH*50)-(*gbH);
				else
					m_coord.y+=m_rate;
			}
		}
		if (event->type == sf::Event::KeyReleased) {m_rate = 10;}
		return used;
	}

	void Camera::validate(int* gbW, int* gbH) {
		if (m_coord.y+m_rate > (m_lmH*50)-(*gbH))
			m_coord.y = (m_lmH*50)-(*gbH);
		if (m_coord.x+m_rate >= (m_lmW*50)-(*gbW))
			m_coord.x = (m_lmW*50)-(*gbW)-1;
	}

} /* namespace graphics */
