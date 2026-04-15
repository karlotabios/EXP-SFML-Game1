#include "RectangleEntity.h"

namespace kt::Shapes {
	RectangleEntity::RectangleEntity() : RectangleShape() {
		setSize(sf::Vector2f{ 100.0f, 100.0f });
		setOrigin(sf::Vector2f{ getSize().x / 2.0f, getSize().y / 2.0f });
		setFillColor(sf::Color::Blue);
	}

	RectangleEntity::~RectangleEntity() {};
}