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

// ostringstream for formatted string concatenation
#include <sstream>

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
		bool m_isKeyLagSpikePressed = false;

		// Debugging features
		unsigned int m_frameCounter = 0;
		const float m_lagSpikeTime = kt::Defaults::LAG_SPIKE_TIME_SECONDS;
		float m_totalSimulationSeconds = 0.0f;
		float m_secondsCounter = 0.0f;
		bool m_isFrictionEnabled = true;
		bool m_isLagSpiking = false;

		std::string m_averageFPSText;

		// Helper functions
		bool handleInput();
		bool handleKeyboardInput();
		bool handleMouseInput();
		bool update();
		void handleObjectMovement();
		void drawScreen();
		void capUPS();
		void trackFPS();
	public:
		CoreSimulation();
		bool initialize();
		bool run();
		bool exitSimulation();
		virtual ~CoreSimulation();
	};
}