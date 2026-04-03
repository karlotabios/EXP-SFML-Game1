#pragma once

// std::cout, std::cin
#include <iostream>

// SFML Graphics
#include <SFML/Graphics.hpp>

// kt::TextEntity Class
#include "../Text/Text.h"

// Hardcoded values
#include "../Defaults/Defaults.h"

// kt::Shapes
#include "../Shapes/Shapes.h"

// std::to_string()
#include <string>

// RNG
#include <random>

#if _DEBUG
#define CONFIG_MODE "DEBUG MODE"
#else
#define CONFIG_MODE "RELEASE MODE"
#endif

namespace kt::Core {
	class CoreSimulation {
	private:
		// Simulation viewport
		sf::Vector2u windowBounds = sf::Vector2u(kt::Defaults::WINDOW_WIDTH, kt::Defaults::WINDOW_HEIGHT);
		sf::RenderWindow window;

		// Game Actors
		kt::Text::TextEntity* movingText = nullptr;
		kt::Text::TextEntity* cornerText = nullptr;
		kt::Shapes::CircleEntity circle;

		// Necessary objects for Actors
		sf::Font font;

		// FPS time tracking
		sf::Clock clock;
		sf::Time elapsedTime;
		sf::Time iterationTime;

		// Helper functions
		void drawScreen();
		void capFPS();
		void deletePointers();
	public:
		CoreSimulation();
		bool initialize();
		bool run();
		bool exitSimulation();
		~CoreSimulation();
	};
}