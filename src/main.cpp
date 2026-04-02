// std::cout, std::cin
#include <iostream>

// SFML Graphics
#include <SFML/Graphics.hpp>

// kt::TextEntity Class
#include "Text/Text.h"

// Hardcoded values
#include "Defaults/Defaults.h"

// kt::Shapes
#include "Shapes/Shapes.h"

// std::to_string()
#include <string>

// RNG
#include <random>

#if _DEBUG
#define CONFIG_MODE "DEBUG MODE"
#else
#define CONFIG_MODE "RELEASE MODE"
#endif

int main()
{
	sf::Vector2u windowBounds(kt::Defaults::WINDOW_WIDTH, kt::Defaults::WINDOW_HEIGHT);
	sf::RenderWindow window(sf::VideoMode(windowBounds), CONFIG_MODE);

	std::default_random_engine rng;
	std::uniform_real_distribution<double> rngDistribution(1, kt::Defaults::WINDOW_HEIGHT);

	// Getting font from file
	sf::Font font(kt::Defaults::FONT_DIR);

	if (!font.openFromFile(kt::Defaults::FONT_DIR)) {
		std::cout << "ERROR: Font not found at path " << kt::Defaults::FONT_DIR << "\n";
	}
	else {
		std::cout << "SUCCESS: Font found at path: " << kt::Defaults::FONT_DIR << "\n";
	}

	// Creating text from font
	kt::Text::TextEntity text(font);
	text.setPosition(sf::Vector2f(kt::Defaults::WINDOW_WIDTH / 2, kt::Defaults::WINDOW_HEIGHT / 2));
	unsigned int fontSize = 44;
	text.setCharacterSize(fontSize);
	text.setFillColor(sf::Color::White);
	text.setVelocity(sf::Vector2f{ 1.0f, 1.0f });

	kt::Text::TextEntity cornerText = text;

	// Creating custom circle
	kt::Shapes::CircleEntity circle;
	float posX = (float)rngDistribution(rng);
	float posY = (float)rngDistribution(rng);
	circle.setPosition(sf::Vector2f(posX, posY));

	// FPS time tracking
	sf::Clock clock;
	sf::Time elapsedTime;
	sf::Time iterationTime;

	while (window.isOpen())
	{
		// Restarting time counter for FPS
		elapsedTime = sf::seconds(0);
		iterationTime = clock.restart();
		elapsedTime += iterationTime;

		// Checking for window events
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			std::cout << "MOUSE CLICK" << std::endl;
		}

		// Track relative mouse position in window
		sf::Vector2i mouseLocalPosition = sf::Mouse::getPosition(window);

		// Set text string
		std::string textContent;
		sf::FloatRect boundingBox = text.getGlobalBounds();
		textContent = std::to_string(boundingBox.position.x) + " " + std::to_string(boundingBox.position.y);
		text.setString(textContent);
		cornerText.setString(textContent);

		circle.setPosition(sf::Vector2f(boundingBox.position.x, boundingBox.position.y));

		// Handle text movement
		//text.move(text.getVelocity());

		// Clearing old frame from display
		window.clear();

		// Draw circle
		window.draw(circle);

		// Drawing text
		window.draw(text);

		window.draw(cornerText);

		// Finally display drawn objects
		window.display();

		// FPS cap
		sf::Time sleepTime = sf::seconds(kt::Defaults::TIMESTEP) - clock.restart();
		if (sleepTime.asSeconds() > 0)
		{
			sf::sleep(sleepTime);
		}
	}
}
