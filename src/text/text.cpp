#include "Text.h"

namespace kt::Text {
	sf::Vector2f TextEntity::getVelocity() const {
		return velocity;
	}
	void TextEntity::setVelocity(const sf::Vector2f& vel) {
		velocity = vel;
	}
}