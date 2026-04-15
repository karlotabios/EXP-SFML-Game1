#include "RectangleEntity.h"

namespace kt::Shapes {
	RectangleEntity::RectangleEntity() : RectangleShape() {
		setSize(sf::Vector2f{ 100.0f, 100.0f });
		setFillColor(sf::Color::Blue);
	}

	RectangleEntity::~RectangleEntity() {};
}