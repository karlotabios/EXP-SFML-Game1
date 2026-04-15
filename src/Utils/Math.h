#pragma once

// kt::Shapes
#include "../Shapes/CircleEntity.h"
#include "../Shapes/RectangleEntity.h"

// std::clamp
#include <algorithm>

namespace kt::Utils {
	// TODO: Create general collision detection for SFML provided rectangle and circles
	// std::optional<sf::Vector2f> detectCollision(const sf::RectangleShape&, const sf::CircleShape&);

	// Returns the collision normal vector of a RectangleEntity shape and a CircleEntity shape if they occupy the same space, a.k.a. collide. Otherwise, returns std::nullopt. Note: This assumes a axis-aligned rectangle shape, and that the shapes have origin points set to their center
	std::optional<sf::Vector2f> detectCollision(const kt::Shapes::RectangleEntity&, const kt::Shapes::CircleEntity&);
}