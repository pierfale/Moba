/*
 * String.hpp
 *
 *  Created on: 26 mai 2013
 *      Author: pierre
 */

#ifndef STRING_HPP_
#define STRING_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <queue>
#include "../../util/Util.hpp"
#include "Component.hpp"

#define BALISE_NONE 0
#define BALISE_OPEN 1
#define BALISE_CLOSE 2
#define BALISE_RETURN 3

#define COLOR_PHYSICALDAMAGE 255,36,0
#define COLOR_MAGICALDAMAGE 58,95,205
#define COLOR_PHYSICALARMOR 139,69,19
#define COLOR_MAGICALARMOR 127,0,255
#define COLOR_ATTACKSPEED 99,184,255
#define COLOR_RANGE 35,142,35
#define COLOR_SPELL 255,255,0


namespace graphics {

	class String : public Component {

	public:
		String(std::string s);
		void set(std::string s);
		void display();
		void draw(sf::RenderWindow* render);
		bool event(sf::Event* event, bool used);


	private:
		void parse(std::string s , util::TagTree* curr);
		int parseBalise(std::string s, StringStyle* style, bool enable);
		void build(util::TagTree* root);
		util::TagTree* m_tree;
		boost::ptr_vector<sf::Text> m_text;

	};
}


#endif /* STRING_HPP_ */
