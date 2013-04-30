/*
 * Gameboard.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: Béni
 */

#include "Gameboard.h"

namespace graphics {

	//standard
	Gameboard::Gameboard(game::GameboardModel* gameboard) : Component(), m_cam() , m_loaded(false) {
		m_gameboardModel = gameboard;
		m_texture = ImageLoader::get("ressources/game/Tiles.png");
		m_player = new Character(m_gameboardModel->getClientPlayer());
		m_oPlayers.push_back(new Character(m_gameboardModel->getOtherPlayer(0)));
		m_loaded = true;
		m_cam.setLandMark(m_gameboardModel->getWidth(), m_gameboardModel->getHeight());
		m_interface = new UserInterface(m_gameboardModel->getClientPlayer());
	}
	Gameboard::~Gameboard() {}

	//graphics manage
	void Gameboard::draw(sf::RenderWindow* render) {
		if (!m_loaded) return;
		drawGameboard(render, m_gameboardModel->getGameboard(0));
		drawGameboard(render, m_gameboardModel->getGameboard(1));
		if (m_player->getPlayerModel()->getCoord().y < m_oPlayers.at(0).getPlayerModel()->getCoord().y) {
			m_player->draw(render, m_cam);
			m_oPlayers.at(0).draw(render, m_cam);
		} else {
			m_oPlayers.at(0).draw(render, m_cam);
			m_player->draw(render, m_cam);
		}
		if (m_player->getPlayerModel()->getSpell()->getCast() && m_player->getPlayerModel()->getSpell()->onRange(m_oPlayers.at(0).getPlayerModel())){
				Animation::draw(render,m_player,NULL);
				if (m_player->getDirection() == 3) m_player->draw(render, m_cam);
		}
		//m_interface->draw(render);
	}

	void Gameboard::drawGameboard(sf::RenderWindow* render, game::Case*** gameboard){
		sf::Sprite* sprite = new sf::Sprite();
		int markX = m_cam.getCoord().x/SIZE_TILE + m_width/SIZE_TILE +2,
				markY = m_cam.getCoord().y/SIZE_TILE + m_height/SIZE_TILE +2;
		if (markY > m_gameboardModel->getHeight()) markY--;if (markY > m_gameboardModel->getHeight()) markY--;if (markX > m_gameboardModel->getHeight()) markX--;
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
				if (event->mouseButton.x >= m_oPlayers.at(0).getPlayerModel()->getCoord().x &&
					event->mouseButton.x < m_oPlayers.at(0).getPlayerModel()->getCoord().x+50 &&
					event->mouseButton.y >= m_oPlayers.at(0).getPlayerModel()->getCoord().y &&
					event->mouseButton.y < m_oPlayers.at(0).getPlayerModel()->getCoord().y+85) {
						m_player->getPlayerModel()->getSpell()->callSpell(0, m_oPlayers.at(0).getPlayerModel());
				}
			}
		}
		m_cam.event(event, &m_width ,&m_height);
		m_player->event(event, m_cam, true);
		m_oPlayers.at(0).event(event, m_cam, false);
		return used;
	}

	void Gameboard::validate() {m_cam.validate(&m_width ,&m_height);}

} /* namespace graphics */
