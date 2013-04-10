/*
 * ImageLoader.hpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#ifndef IMAGELOADER_HPP_
#define IMAGELOADER_HPP_

#include <string>
#include <vector>
#include <map>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <SFML/Graphics.hpp>
#include "../log/Log.hpp"

namespace graphics {

	class ImageLoader {

	public:
		ImageLoader();
		void add(std::string path);
		void process();
		sf::Texture* get(std::string path);

	private:
		std::map<std::string,sf::Texture> m_textures;
		std::vector<std::string> m_wait;
		boost::mutex m_guard;
	};

}

#endif /* IMAGELOADER_HPP_ */
