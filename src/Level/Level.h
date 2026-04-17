#pragma once

#include <SFML/Graphics.hpp>

namespace kt::Level {
	class LevelManager {
	public:
		std::vector<sf::Drawable*> m_geometry{};

		LevelManager();
		virtual ~LevelManager();
	};
}