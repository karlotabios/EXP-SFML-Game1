#pragma once

// std::cout, std::cin
#include <iostream>

// SFML Graphics
#include <SFML/Graphics.hpp>

// kt::TextEntity Class
#include "../Text/Text.h"

// Hardcoded values
#include "../Globals/Defaults.h"

// kt::Shapes
#include "../Shapes/CircleEntity.h"
#include "../Shapes/RectangleEntity.h"

// std::to_string()
#include <string>

// RNG
#include <random>

// Windows System commands, std::system
#include <cstdlib>

// ostringstream for formatted string concatenation
#include <sstream>

// kt::Frametime struct
#include "../Utils/Frametime.h"

// detectCollision function
#include "../Utils/Math.h"

#if _DEBUG
#define CONFIG_MODE "DEBUG MODE"
#else
#define CONFIG_MODE "RELEASE MODE"
#endif

namespace kt::Core {
	class CoreSimulation {
	private:
		// Simulation viewport
		sf::Vector2u m_windowBounds = sf::Vector2u(kt::Globals::WINDOW_WIDTH, kt::Globals::WINDOW_HEIGHT);
		sf::RenderWindow m_window{};

		// Necessary objects for Actors
		sf::Font m_font{};

		// Game Actors
		kt::Text::TextEntity m_movingText{ m_font };
		kt::Text::TextEntity m_cornerText{ m_font };
		kt::Shapes::CircleEntity m_circle{};
		kt::Shapes::RectangleEntity m_rectangle{};

		// Static geometry
		sf::RectangleShape m_centerVerticalLine{};
		sf::RectangleShape m_centerHorizontalLine{};

		// Helper containers
		std::vector<sf::Drawable*> m_drawableObjects = {
			&m_rectangle,
			&m_centerVerticalLine,
			&m_centerHorizontalLine,
			&m_circle,
			&m_movingText,
			&m_cornerText,
		};

		// Time tracking
		kt::Utils::Frametime m_Time{};

		// Key-press tracking
		bool m_isKeyFrictionPressed = false;
		bool m_isKeyLagSpikePressed = false;

		// Debugging features
		const float m_lagSeconds = kt::Globals::LAG_SPIKE_TIME_SECONDS;
		float m_secondsCounter = 0.0f;
		bool m_isFrictionEnabled = true;
		bool m_isLagSpikeEnabled = false;

		std::string m_averageFPSText;

		// Helper functions
		void handleKeyboardInput();
		void handleMouseInput();
		void handleObjectMovement();
		void handleObjectOutOfBounds();
		void handleUI();
		void handleObjectState();
		
		// Primary functions
		void handleInput();
		void update();
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