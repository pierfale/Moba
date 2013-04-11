/*
 * ImageLoader.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#include "ImageLoader.hpp"

namespace graphics {


	ImageLoader* ImageLoader::m_instance = NULL;

	ImageLoader::ImageLoader() {

	}


	sf::Texture* ImageLoader::get(std::string path) {

		client::Log::out("[ImageLoader] get "+path);
		if(getInstance()->m_textures.find(path) == getInstance()->m_textures.end()) {
			sf::Texture curr;
			curr.loadFromFile(path);
			getInstance()->m_textures[path] = curr;
		}
		return &getInstance()->m_textures[path];
	}

	ImageLoader* ImageLoader::getInstance() {
		if(m_instance == NULL)
			m_instance = new ImageLoader();
		return m_instance;
	}
}

