#pragma once

#include <SFML/Graphics.hpp>

namespace kt::Utils {
	// Frametime is a plain-old-data struct intended to track frame and time related data within a simulation loop
	struct Frametime {
		unsigned int frameCounter{};
		sf::Clock clock{};
		sf::Time elapsedTime{};		// Actual time per frame
		sf::Time deltaTime{};		// Amount of time to be used in a single tick of simulation
		sf::Time totalTime{};
	};
}