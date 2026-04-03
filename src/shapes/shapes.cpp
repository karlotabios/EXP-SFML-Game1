#include "Shapes.h"
#include "../Physical/Movable.h"

namespace kt::Shapes {
	CircleEntity::CircleEntity() : CircleShape() {
		setRadius(150.0f);
		setOrigin(sf::Vector2f(getRadius(), getRadius()));
		setFillColor(sf::Color::Red);
		setOutlineColor(sf::Color::Red);
	}
}