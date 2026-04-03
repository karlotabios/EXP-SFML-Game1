#pragma once

#include <SFML/Graphics.hpp>

namespace kt::Defaults {
	static const float FPS = 60.0f;
	static const float TIMESTEP = (1.0f / FPS);
	static const float WINDOW_HEIGHT = 600.0f;
	static const float WINDOW_WIDTH = 800.0f;
	static const std::string FONT_DIR = "../font/Roboto/Roboto-VariableFont_wdth,wght.ttf";
	/*static const std::string FONT_DIR = "../font/Roboto/static/Roboto_Condensed-Black.ttf";*/
}