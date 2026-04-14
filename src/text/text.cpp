#include "Text.h"

namespace kt::Text {
	TextEntity::TextEntity(const sf::Font& font) : sf::Text(font) {};

	sf::Vector2f TextEntity::getVelocity() const {
		return m_velocity;
	}

	void TextEntity::setVelocity(const sf::Vector2f& vel) {
		m_velocity = vel;
	}
}