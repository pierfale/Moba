#include "ShotAnim.hpp"

namespace graphics {

	ShotAnim::ShotAnim(game::Character* caster, game::Character* target, std::string image, int nFrame) : SingleTargetSpellAnim(caster, target), m_nFrame(nFrame) {
		m_texture = ImageLoader::get(image);
		m_frame = 0;
		m_first = true;
		m_frameLength = 0.2;
		m_speed = 100;
		m_coord = caster->getCoord();
	}

	int ShotAnim::getValueY() {
		return m_coord.y;
	}

	void ShotAnim::draw(sf::RenderWindow* render, Camera* cam) {
		float length = 0;
		if(m_first) {
			m_first = false;
			m_timer.restart();
			m_lastDraw.restart();
		}
		else {
			length = m_lastDraw.elapsed()*m_speed;
			m_lastDraw.restart();
		}

		if(m_timer.elapsed() > m_frameLength) {
			m_frame++;
			m_timer.restart();
		}

		if(m_frame >= m_nFrame)
			m_frame = 0;

		float angle = util::Math::angle(m_target->getCoord(), m_coord);
		m_coord.x += length*cos(angle);
		m_coord.y += length*sin(angle);

		if(m_caster->getCoord().x  < m_target->getCoord().x && m_coord.x > m_target->getCoord().x)
			m_coord.x = m_target->getCoord().x;
		if(m_caster->getCoord().x  > m_target->getCoord().x && m_coord.x < m_target->getCoord().x)
			m_coord.x = m_target->getCoord().x;
		if(m_caster->getCoord().y  < m_target->getCoord().y && m_coord.y > m_target->getCoord().y)
			m_coord.y = m_target->getCoord().y;
		if(m_caster->getCoord().y  > m_target->getCoord().y && m_coord.y < m_target->getCoord().y)
			m_coord.y = m_target->getCoord().y;

		if(m_coord.x == m_target->getCoord().x && m_coord.y == m_target->getCoord().y) {
			m_done = true;
			return;
		}

		sf::Sprite sprite;
		sprite.setTexture(*m_texture);
		sprite.setPosition(m_coord.x-cam->getCoord().x, m_coord.y-45-cam->getCoord().y);
		sprite.setTextureRect(sf::IntRect(m_frame*m_texture->getSize().x/m_nFrame, 0, m_texture->getSize().x/m_nFrame, m_texture->getSize().y));
		sprite.setOrigin((m_texture->getSize().x/m_nFrame)/2, m_texture->getSize().y/2);
		sprite.setRotation(angle);
		render->draw(sprite);


	}
}
