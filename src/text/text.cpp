#include "text.h"

namespace kt::text {
	sf::Vector2f TextEntity::getVelocity() const {
		return velocity;
	}
	void TextEntity::setVelocity(const sf::Vector2f& vel) {
		velocity = vel;
	}
}