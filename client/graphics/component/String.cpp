/*
 * String.cpp
 *
 *  Created on: 26 mai 2013
 *      Author: pierre
 */

#include "String.hpp"

namespace graphics {

	String::String(std::string s) {
		m_tree = new util::TagTree();
		parse(s, m_tree);
		build(m_tree);
	}
	void String::set(std::string s) {
		parse(s, m_tree);
		build(m_tree);
	}

	void String::parse(std::string s, util::TagTree* curr) {
		unsigned int i = 0;
		unsigned int begContents = 0;
		unsigned int begBalise = 0;
		bool balise = false;
		int nBalise = 0;
		StringStyle* currStyle = curr->getStyle();
		StringStyle* currStyleIn = curr->getStyle()->copy();
		while(i < s.size()) {
			if(s.at(i) == '<') {
				balise = true;
				begBalise = i;
				if(begContents != i && nBalise == 0) {
					std::string c = s.substr(begContents, i-begContents);
					util::TagTree* tt = new util::TagTree(currStyle->copy());
					tt->setContents(c);
					curr->addChild(tt);
				}
			}
			else if(s.at(i) == '>' && balise) {
				balise = false;
				std::string b = s.substr(begBalise, i-begBalise+1);
				int r = parseBalise(b, currStyleIn, nBalise == 0);
				if(r == BALISE_OPEN) {
					if(nBalise == 0) {
						begContents = i+1;
					}
					nBalise++;
				}
				else if(r == BALISE_CLOSE) {
					nBalise--;
					if(nBalise == 0) {
						std::string c = s.substr(begContents, begBalise-begContents);
						util::TagTree* tt = new util::TagTree(currStyleIn);
						curr->addChild(tt);
						parse(c, tt);
						begContents = i+1;
						currStyleIn = currStyle->copy();
					}
				}
				else if(r == BALISE_RETURN && nBalise == 0) {
					util::TagTree* tt = new util::TagTree();
					tt->setContents("\n");
					curr->addChild(tt);
					begContents = i+1;
				}
			}
			i++;
		}
		if(begContents != i) {
			std::string c = s.substr(begContents, i-begContents);
			util::TagTree* tt = new util::TagTree(currStyle->copy());
			tt->setContents(c);
			curr->addChild(tt);
		}


	}

	int String::parseBalise(std::string s, StringStyle* style, bool enable) {

		if(s == "<br>" || s == "<br/>")
			return BALISE_RETURN;
		else if(s.at(1) != '/' && s.at(s.length()-1) != '/') {
			if(enable) {
				if(s.length() > 8 && s.substr(1, 6) == "color=") {
					if(s.at(7) >= '0' && s.at(7) <= '9') {
						int color[3];
						unsigned int i = 7;
						unsigned int beg = 7;
						int nColor = 0;
						while(i < s.length()) {
							if(s.at(i) == ',' || (nColor == 2 && (s.at(i) == '>' || s.at(i) == ' '))) {
								color[nColor] = util::Cast::stringToInt(s.substr(beg, i-beg));
								nColor++;
								beg = i+1;
							}
							i++;
						}
						if(nColor == 3) {
							style->setColor(sf::Color(color[0], color[1], color[2]));
						}
					}
					else {
						if(s.substr(7, s.length()-8) == "pd")
							style->setColor(sf::Color(COLOR_PHYSICALDAMAGE));
						else if(s.substr(7, s.length()-8) == "md")
							style->setColor(sf::Color(COLOR_MAGICALDAMAGE));
						else if(s.substr(7, s.length()-8) == "pa")
							style->setColor(sf::Color(COLOR_PHYSICALARMOR));
						else if(s.substr(7, s.length()-8) == "ma")
							style->setColor(sf::Color(COLOR_MAGICALARMOR));
						else if(s.substr(7, s.length()-8) == "as")
							style->setColor(sf::Color(COLOR_ATTACKSPEED));
						else if(s.substr(7, s.length()-8) == "ra")
							style->setColor(sf::Color(COLOR_RANGE));
						else if(s.substr(7, s.length()-8) == "sp")
							style->setColor(sf::Color(COLOR_SPELL));
						style->setBold(true);
						style->setItalic(true);

					}
				}
				else if(s.length() == 3 && s.substr(1, 1) == "u") {
					style->setUnderline(true);
				}
				else if(s.length() == 3 && s.substr(1, 1) == "b") {
					style->setBold(true);
				}
				else if(s.length() == 3 && s.substr(1, 1) == "i") {
					style->setItalic(true);
				}
				else if(s.length() > 7 && s.substr(1, 5) == "size=") {
					style->setSize(util::Cast::stringToInt(s.substr(6, s.size()-2)));
				}
			}
			return BALISE_OPEN;
		}
		else if(s.at(1) == '/') {
			return BALISE_CLOSE;
		}
		return BALISE_NONE;
	}

	void String::build(util::TagTree* root) {
		m_text.clear();
		int currX = 0, currY = 0;
		int maxHeightLine = 0, maxHeightLineLast = 0;
		int maxWidth = 0;
		boost::ptr_deque<util::TagTree> m_stack;
		m_stack.push_back(root);
		while(m_stack.size() > 0) {
			util::TagTree* curr = m_stack.pop_back().release();
			if(curr->getContents() == "\n") {

				if(maxHeightLine != 0) {
					currY += maxHeightLine+2;
					maxHeightLineLast = maxHeightLine;
				}
				else {
					if(maxHeightLineLast == 0) {
						maxHeightLineLast = 12;
					}
					currY += maxHeightLineLast+2;
				}
				maxHeightLine = 0;
				if(maxWidth < currX)
					maxWidth = currX;
				currX = 0;
			}
			else if(curr->getContents() != "") {
				if(curr->getContents().at(0) == ' ')
					currX += curr->getStyle()->size()/4;
				sf::Text* text = new sf::Text(curr->getContents());
				text->setColor(curr->getStyle()->color());
				text->setCharacterSize(curr->getStyle()->size());
				text->setStyle(curr->getStyle()->style());
				text->setPosition(currX, currY);
				m_text.push_back(text);
				currX += text->getGlobalBounds().width;
				if(curr->getContents().at(curr->getContents().size()-1) == ' ' && curr->getContents().size() > 2)
					currX += curr->getStyle()->size()/4;
				if(curr->getStyle()->size() > maxHeightLine)
					maxHeightLine = curr->getStyle()->size();
			}

			for(int i=curr->getChildSize()-1; i>=0; i--)
				m_stack.push_back(curr->getChild(i));
		}

		if(maxWidth < currX)
			maxWidth = currX;

		m_width = maxWidth;
		m_height = currY+maxHeightLine+3;
	}

	void String::draw(sf::RenderWindow* render) {
		util::CoordInt coord = getRealCoord();
		for(unsigned int i=0; i<m_text.size(); i++) {
			sf::Vector2f old = m_text.at(i).getPosition();
			m_text.at(i).setPosition(old.x+coord.x, old.y+coord.y);
			render->draw(*(&m_text.at(i)));
			m_text.at(i).setPosition(old);
		}
	}

	bool String::event(sf::Event* event, bool used) {
		return used;
	}

	void String::display() {
		m_tree->display(0);
	}
}


