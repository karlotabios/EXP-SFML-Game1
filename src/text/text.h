#pragma once

#include <SFML/Graphics.hpp>

namespace kt::Text {
	class TextEntity : public sf::Text {
	private:
		sf::Vector2f velocity = { 0.0f, 0.0f };
	public:
		TextEntity(const sf::Font& font);
		sf::Vector2f getVelocity() const;
		void setVelocity(const sf::Vector2f& vel);
	};
}