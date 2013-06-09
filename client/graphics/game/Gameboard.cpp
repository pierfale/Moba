/*
 * Gameboard.cpp
 *
 *  Created on: 8 avr. 2013
 *      Author: Béni
 */

#include "Gameboard.h"
#include "ui/UserInterface.h"

namespace graphics {

	Camera Gameboard::m_cam;
	 boost::ptr_vector<Animation> Gameboard::m_animations;

	//standard
	Gameboard::Gameboard(std::string map) : Container(), m_loaded(false) {

		game::GameboardModel::read(map);

		m_texture = ImageLoader::get("ressources/game/Tiles.png");

		Cursor::set(CURSOR_GAMENORMAL);
		UserPlayer* m_userPlayer = new UserPlayer(game::CurrentCharacter::get());

		game::CurrentCharacter::set(m_userPlayer);
		for(int i=0; i<game::GamePlayerList::size(); i++) {
			m_players.push_back(new Player(game::GamePlayerList::get(i)));
		}

		m_players.push_back(m_userPlayer);

		m_cam.setLandMark(game::GameboardModel::getWidth(), game::GameboardModel::getHeight());

		if (game::CurrentCharacter::get()->getFaction() == network::PacketType::FACTION_TEAM1)
			m_cam.setCoord(util::CoordInt(5,5));
		else
			m_cam.setCoord(util::CoordInt(1100,1100));

		m_interface = new UserInterface(game::CurrentCharacter::get(), "ressources/game/Battleground", this);
		add(m_interface);
	}
	Gameboard::~Gameboard() {
		delete m_interface;
	}

	bool characterSort(Character* c1, Character* c2) {
		return c1->getModel()->getCoord().y < c2->getModel()->getCoord().y;
	}

	//graphics manage
	void Gameboard::draw(sf::RenderWindow* render) {
		if (!m_loaded) {
				m_interface->buildTeam();
				m_interface->setMode();
				m_loaded = true;
		}

		//update character
		for(unsigned int i=0; i<m_players.size(); i++) {
			m_players.at(i).update();
		}

		//delete done animation
		bool release;
		do {
			release = false;
			for(boost::ptr_vector<Animation>::iterator it = m_animations.begin(); !release && it != m_animations.end(); it++) {
				if(it->isDone()) {
					m_animations.release(it);
					release = true;
				}
			}
		} while(release);

		drawGameboard(render, game::GameboardModel::getGameboard(0));
		drawGameboard(render, game::GameboardModel::getGameboard(1));

		 // std::cout << m_animations.size() << std::endl;

		for(unsigned int i=0; i<m_animations.size(); i++) {
			m_bufferY.add(&m_animations.at(i));
		}

		for(unsigned int i=0; i<m_players.size(); i++) {
			m_bufferY.add(&m_players.at(i));
		}

		m_bufferY.draw(render, &m_cam);
		m_interface->draw(render);

		m_bufferY.clear();

		if(m_messageTimer.elapsed() < 3.0)
			render->draw(m_message);
	}

	void Gameboard::drawGameboard(sf::RenderWindow* render, game::Case*** gameboard){
		//Check mouse move camera
		if(m_window->isFocus()) {
			util::CoordInt mouse = util::CoordInt(sf::Mouse::getPosition(*render).x, sf::Mouse::getPosition(*render).y);
			int borderSize = 30;
			if(mouse.x < borderSize && mouse.x >= 0)
				m_cam.move(true, false);
			if(mouse.x > render->getSize().x-borderSize && mouse.x <= render->getSize().x)
				m_cam.move(true, true);
			if(mouse.y < borderSize && mouse.y >= 0)
				m_cam.move(false, false);
			if(mouse.y > render->getSize().y-borderSize && mouse.y <= render->getSize().y)
				m_cam.move(false, true);

			m_cam.endMove();
		}

		sf::Sprite sprite;
		int markX = m_cam.getCoord().x/SIZE_TILE + m_width/SIZE_TILE +2,
				markY = m_cam.getCoord().y/SIZE_TILE + m_height/SIZE_TILE +2;
		if (markY > game::GameboardModel::getHeight()) markY--;
		if (markY > game::GameboardModel::getHeight()) markY--;
		if (markX > game::GameboardModel::getHeight()) markX--;
 		for (int i = m_cam.getCoord().y/SIZE_TILE, k = 0 ; i < markY ; i++, k++){
			for (int j = m_cam.getCoord().x/SIZE_TILE, l = 0; j < markX ; j++, l++){
				if (gameboard[j][i]->getId() != 0) {
 					sprite.setTexture(*m_texture);
					sf::Rect<int> spriteZone((gameboard[j][i]->getId()*50)%200,((gameboard[j][i]->getId()*50)/200)*50,SIZE_TILE,SIZE_TILE);
					sprite.setTextureRect(spriteZone);
					sprite.setPosition((l*SIZE_TILE)-m_cam.getCoord().x%SIZE_TILE,(k*SIZE_TILE)-m_cam.getCoord().y%SIZE_TILE);
					render->draw(sprite);
				}
			}
		}
	}

	bool Gameboard::event(sf::Event* event, bool used) {
		used = m_cam.event(event, used, &m_width ,&m_height);
		used = m_interface->event(event, used);
		for(unsigned int i=0; i<m_players.size(); i++)
			used = m_players.at(i).event(event, &m_cam, used);
		if(!used && event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left) {
			used = true;
			network::Packet packet(network::Network::getSocket(), network::PacketType::GAME_ASKTARGET);
			packet << 0;
			packet.send();

		}

		if(event->type == sf::Event::MouseButtonPressed) {
			Cursor::set(CURSOR_GAMENORMAL);
			game::CurrentSpell::set(NULL);
		}

		return used;
	}

	void Gameboard::validate() {m_cam.validate(&m_width ,&m_height);Container::validate();
	}

	void Gameboard::loadImage() {
		ImageLoader::get("ressources/game/Tiles.png");
		ImageLoader::get("ressources/game/1.png");
		ImageLoader::get("ressources/game/animSword.png");
	}

	util::CoordInt Gameboard::convertCoord(util::CoordInt coord) {
		return util::CoordInt(coord.x-m_cam.getCoord().x, coord.y-m_cam.getCoord().y);
	}

	util::CoordFloat Gameboard::convertCoord(util::CoordFloat coord) {
		return util::CoordFloat(coord.x-(float)m_cam.getCoord().x, coord.y-(float)m_cam.getCoord().y);
	}

	void Gameboard::addAnimation(Animation* animation) {
		m_animations.push_back(animation);
	}

	void Gameboard::removeAnimation(Animation* animation) {
		for(boost::ptr_vector<Animation>::iterator it = m_animations.begin(); it != m_animations.end(); it++) {
			if(&(*it) == animation) {
				m_animations.release(it);
				return;
			}
		}
	}

	Chat* Gameboard::getChat() {
		return m_interface->getChat();
	}

	std::string Gameboard::getComponentName() {
		return "Gameboard";
	}

	std::string Gameboard::getName() {
		return "Gameboard";
	}

	Camera* Gameboard::getCamera() {
		return &m_cam;

	}

	void Gameboard::setMessage(std::string message) {
		m_message.setString(message);
		m_message.setCharacterSize(20);
		m_message.setPosition((m_width-m_message.getGlobalBounds().width)/2, m_height-150);
		m_messageTimer.restart();
	}

} /* namespace graphics */
