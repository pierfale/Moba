/*
 * ImageLoader.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#include "ImageLoader.hpp"



namespace graphics {

	boost::mutex ImageLoader::m_guard;

	ImageLoader::ImageLoader() {

	}

	void ImageLoader::add(std::string path) {
		boost::mutex::scoped_lock lock(m_guard);
		if(m_textures.find(path) == m_textures.end())
			m_wait.push_back(path);
	}

	void  ImageLoader::process() {
		boost::mutex::scoped_lock lock(m_guard);
		for(std::vector<std::string>::iterator it = m_wait.begin() ; it != m_wait.end(); ++it) {
			sf::Texture curr;
			curr.loadFromFile(*it);
			m_textures[*it] = curr;
			client::Log::out("[ImageLoader] "+(*it)+" loaded");
		}
		m_wait.clear();
	}

	sf::Texture* ImageLoader::get(std::string path) {
		while(m_textures.find(path) == m_textures.end()) {
			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
		}
		return &m_textures[path];
	}
}

