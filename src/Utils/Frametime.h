#pragma once

#include <SFML/Graphics.hpp>

namespace kt::Utils {
	// Frametime is a plain-old-data struct intended to track frame and time related data within a simulation loop
	struct Frametime {
		unsigned int frameCounter{};
		float secondsAccumulator{};
		sf::Clock clock{};
		sf::Time simulationTime{};		// Time within the simulation
		sf::Time realTime{};				// Time throught the entire lifetime of object owning this
		sf::Time deltaTime{};					// Amount of time to be used in a single tick of simulation
		
		float fpsDisplayAccumulator{};
	};
}