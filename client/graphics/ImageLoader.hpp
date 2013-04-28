/*
 * ImageLoader.hpp
 *
 *  Created on: 8 avr. 2013
 *      Author: pierre
 */

#ifndef IMAGELOADER_HPP_
#define IMAGELOADER_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>

//Log
#include "../log/Log.hpp"
//Debug
#include "../debug/Alloc.hpp"

namespace graphics {

	class ImageLoader {

	public:
		~ImageLoader();
		static sf::Texture* get(std::string path);
		static void process();
	private:
		ImageLoader();
		std::map<std::string,sf::Texture> m_textures;
		std::vector<std::string> m_wait;
		static ImageLoader* getInstance();
		static boost::shared_ptr<ImageLoader> m_instance;
		boost::mutex m_guard;

	};

}

#endif /* IMAGELOADER_HPP_ */
