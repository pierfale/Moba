/*
 * ImageLoader.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#include "ImageLoader.hpp"

namespace graphics {


	boost::shared_ptr<ImageLoader> ImageLoader::m_instance;

	ImageLoader::ImageLoader() {

	}

	ImageLoader::~ImageLoader() {
		m_instance.reset();
	}


	sf::Texture* ImageLoader::get(std::string path) {

		log_out "[ImageLoader] get "+path end_log_out;
		if(getInstance()->m_textures.find(path) == getInstance()->m_textures.end()) {
			sf::Texture curr;
			curr.loadFromFile(path);
			getInstance()->m_textures[path] = curr;
			getInstance()->m_images[path] = curr.copyToImage();
		}
		return &getInstance()->m_textures[path];
	}

	sf::Image* ImageLoader::getImage(std::string path) {
		if(getInstance()->m_images.find(path) == getInstance()->m_images.end())
			return NULL;
		else
			return &getInstance()->m_images[path];
	}

	void ImageLoader::process() {
		 for(std::vector<std::string>::iterator it = getInstance()->m_wait.begin() ; it != getInstance()->m_wait.end(); ++it) {
			 getInstance()->m_textures[*it].loadFromFile(*it);
			 log_out "[ImageLoader] loaded "+(*it) end_log_out;
		 }
		 getInstance()->m_wait.clear();

	}

	ImageLoader* ImageLoader::getInstance() {
		if(m_instance.get() == NULL)
			m_instance.reset(new ImageLoader());
		return m_instance.get();
	}
}

