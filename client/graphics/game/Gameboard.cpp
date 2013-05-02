/*
 * Gameboard.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: Béni
 */

#include "Gameboard.h"

namespace graphics {

	//standard
	Gameboard::Gameboard() : Container(), m_cam() , m_loaded(false) {
		m_texture = ImageLoader::get("ressources/game/Tiles.png");
		m_player = new Character(game::CurrentCharacter::get());

		for(int i=0; i<game::GamePlayerList::size(); i++) {
			m_oPlayers.push_back(new Character(game::GamePlayerList::get(i)));
		}

		m_loaded = true;
		m_cam.setLandMark(game::GameboardModel::getWidth(), game::GameboardModel::getHeight());
		m_interface = new UserInterface(game::CurrentCharacter::get());
	}
	Gameboard::~Gameboard() {}

	//graphics manage
	void Gameboard::draw(sf::RenderWindow* render) {
		if (!m_loaded) return;

		m_player->updateCoord();
		for(unsigned int i=0; i<m_oPlayers.size(); i++) {
			m_oPlayers.at(i).calculCoord();
		}
		drawGameboard(render, game::GameboardModel::getGameboard(0));
		drawGameboard(render, game::GameboardModel::getGameboard(1));
		bool playerDraw = false;
		for(unsigned int i=0; i<m_oPlayers.size(); i++) {
			if(!playerDraw && m_player->getModel()->getCoord().y < m_oPlayers.at(i).getModel()->getCoord().y) {
				playerDraw = true;
				m_player->draw(render, &m_cam);
			}
			m_oPlayers.at(i).draw(render, &m_cam);
		}
		if(!playerDraw)
			m_player->draw(render, &m_cam);

		//wtf?
		/*if (m_player->getPlayerModel()->getSpell()->getCast() && m_player->getPlayerModel()->getSpell()->onRange(m_oPlayers.at(0).getPlayerModel())){
				Animation::draw(render,m_player,NULL);
				if (m_player->getDirection() == 3) m_player->draw(render, m_cam);
		}*/
		//m_interface->draw(render);
	}

	void Gameboard::drawGameboard(sf::RenderWindow* render, game::Case*** gameboard){
		sf::Sprite* sprite = new sf::Sprite();
		int markX = m_cam.getCoord().x/SIZE_TILE + m_width/SIZE_TILE +2,
				markY = m_cam.getCoord().y/SIZE_TILE + m_height/SIZE_TILE +2;
		if (markY > game::GameboardModel::getHeight()) markY--;if (markY >game::GameboardModel::getHeight()) markY--;if (markX > game::GameboardModel::getHeight()) markX--;
 		for (int i = m_cam.getCoord().y/SIZE_TILE, k = 0 ; i < markY ; i++, k++){
			for (int j = m_cam.getCoord().x/SIZE_TILE, l = 0; j < markX ; j++, l++){
				if (gameboard[j][i]->getId() != 0) {
					sprite->setTexture(*m_texture);
					sf::Rect<int> spriteZone((gameboard[j][i]->getId()*50)%200,((gameboard[j][i]->getId()*50)/200)*50,SIZE_TILE,SIZE_TILE);
					sprite->setTextureRect(spriteZone);
					sprite->setPosition((l*SIZE_TILE)-m_cam.getCoord().x%SIZE_TILE,(k*SIZE_TILE)-m_cam.getCoord().y%SIZE_TILE);
					render->draw(*sprite);
				}
			}
		}
 		free(sprite);
	}

	bool Gameboard::event(sf::Event* event, bool used) {
		if (event->type == sf::Event::MouseButtonPressed) {
			if (event->mouseButton.button == sf::Mouse::Right) {
				/*if (event->mouseButton.x >= m_oPlayers.at(0).getPlayerModel()->getCoord().x &&
					event->mouseButton.x < m_oPlayers.at(0).getPlayerModel()->getCoord().x+50 &&
					event->mouseButton.y >= m_oPlayers.at(0).getPlayerModel()->getCoord().y &&
					event->mouseButton.y < m_oPlayers.at(0).getPlayerModel()->getCoord().y+85) {
						m_player->getPlayerModel()->getSpell()->callSpell(0, m_oPlayers.at(0).getPlayerModel());
				}*/
			}
		}
		m_cam.event(event, &m_width ,&m_height);
		m_player->event(event, &m_cam, used, true);

		for(unsigned int i=0; i<m_oPlayers.size(); i++)
			m_oPlayers.at(i).event(event, &m_cam, used, false);
		return used;
	}

	void Gameboard::validate() {m_cam.validate(&m_width ,&m_height);}

	void Gameboard::loadImage() {
		ImageLoader::get("ressources/game/Tiles.png");
		ImageLoader::get("ressources/game/1.png");
		ImageLoader::get("ressources/game/animSword.png");
		game::GameboardModel::read("ressources/game/mapOfArena");
	}

} /* namespace graphics */
