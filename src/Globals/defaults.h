#pragma once

#include <SFML/Graphics.hpp>

namespace kt::Globals {
	static constexpr unsigned int ANTI_ALIASING_LEVEL = 8;
	static constexpr float FPS = 60.0f;
	static constexpr float TIMESTEP = (1.0f / FPS);
	static constexpr float WINDOW_HEIGHT = 1040.0f;
	static constexpr float WINDOW_WIDTH = 1920.0f;
	static const std::string FONT_FILE_PATH = "../font/Roboto/Roboto-VariableFont_wdth,wght.ttf";
	static const std::string LAG_IMAGE_FILE_PATH = "../img/lag.png";
	static constexpr float STATIC_FRICTION_COEF = 0.75f;		// Values ideally clamped from 0.0f to 1.0f
	static constexpr float KINETIC_FRICTION_COEF = 0.5f;	// Values ideally clamped from 0.0f to 1.0f
	static constexpr float GRAVITY_ACCELERATION = 1000.0f;
	static constexpr sf::Vector2f PLAYER_MOVEMENT_FORCE{ 10000.0f, 10000.0f };
	static constexpr float LAG_SPIKE_TIME_SECONDS = 1.0f;
}