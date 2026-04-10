#pragma once

#include <SFML/Graphics.hpp>

// std::clamp
#include <algorithm>

namespace kt::Defaults {
	static const unsigned int ANTI_ALIASING_LEVEL = 8;
	static const float FPS = 60.0f;
	static const float TIMESTEP = (1.0f / FPS);
	static const float WINDOW_HEIGHT = 1040.0f;
	static const float WINDOW_WIDTH = 1920.0f;
	static const std::string FONT_DIR = "../font/Roboto/Roboto-VariableFont_wdth,wght.ttf";
	static const float STATIC_FRICTION_COEF = 0.5f;		// Values ideally clamped from 0.0f to 1.0f
	static const float KINETIC_FRICTION_COEF = 0.3f;	// Values ideally clamped from 0.0f to 1.0f
	static const float GRAVITY_ACCELERATION = 9.8f;
	static const sf::Vector2f PLAYER_MOVEMENT_FORCE{ 150.0f, 150.0f };
}