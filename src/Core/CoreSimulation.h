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
#include "../Shapes/CircleEntity.h"

// std::to_string()
#include <string>

// RNG
#include <random>

// Windows System commands, std::system
#include <cstdlib>

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
		sf::RenderWindow m_window{};

		// Necessary objects for Actors
		sf::Font m_font{};

		// Game Actors
		kt::Text::TextEntity m_movingText{ m_font };
		kt::Text::TextEntity m_cornerText{ m_font };
		kt::Shapes::CircleEntity m_circle{};

		// FPS time tracking
		sf::Clock m_clock{};
		sf::Time m_elapsedTime{};
		sf::Time m_iterationTime{};

		// Key-press tracking
		bool m_isKeyFrictionPressed = false;

		// Debugging features
		bool m_isFrictionEnabled = true;

		// Helper functions
		void drawScreen();
		void capFPS();
		bool handleKeyboardInput();
		bool handleMouseInput();
		void handleObjectMovement();
		void deleteAllPointers();
	public:
		CoreSimulation();
		bool initialize();
		bool run();
		bool exitSimulation();
		virtual ~CoreSimulation();
	};
}