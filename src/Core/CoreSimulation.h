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
		sf::Vector2u m_windowBounds = sf::Vector2u(kt::Defaults::WINDOW_WIDTH, kt::Defaults::WINDOW_HEIGHT);
		sf::RenderWindow m_window;

		// Game Actors
		kt::Text::TextEntity* m_movingText = nullptr;
		kt::Text::TextEntity* m_cornerText = nullptr;
		kt::Shapes::CircleEntity m_circle;

		// Necessary objects for Actors
		sf::Font m_font;

		// FPS time tracking
		sf::Clock m_clock;
		sf::Time m_elapsedTime;
		sf::Time m_iterationTime;

		// Helper functions
		void drawScreen();
		void capFPS();
		void deleteAllPointers();
	public:
		CoreSimulation();
		bool initialize();
		bool run();
		bool exitSimulation();
		~CoreSimulation();
	};
}