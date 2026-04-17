#pragma once

#include <SFML/Graphics.hpp>

namespace kt::Utils {
	// Frametime is a plain-old-data struct intended to track frame and time related data within a simulation loop
	struct Frametime {
		unsigned int frameCounter{};
		sf::Clock clock{};
		sf::Time elapsedTime{};
		sf::Time deltaTime{};
		sf::Time totalTime{};
	};
}