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
		static sf::Texture* get(std::string path);

	private:
		std::map<std::string,sf::Texture> m_textures;
		static ImageLoader* getInstance();
		static ImageLoader* m_instance;

	};

}

#endif /* IMAGELOADER_HPP_ */
