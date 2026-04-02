// std::cout, std::cin
#include <iostream>

// SFML Graphics
#include <SFML/Graphics.hpp>

// kt::TextEntity Class
#include "text/text.h"

// Hardcoded values
#include "defaults/defaults.h"

// std::to_string()
#include <string>

#if _DEBUG
#define CONFIG_MODE "DEBUG MODE"
#else
#define CONFIG_MODE "RELEASE MODE"
#endif

int main()
{
	sf::Vector2u windowBounds = sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT);
	sf::RenderWindow window(sf::VideoMode(windowBounds), CONFIG_MODE);

	// Getting font from file
	sf::Font font(FONT_DIR);

	if (!font.openFromFile(FONT_DIR)) {
		std::cout << "ERROR: Font not found at path " << FONT_DIR << "\n";
	}
	else {
		std::cout << "SUCCESS: Font found at path: " << FONT_DIR << "\n";
	}

	// Creating text from font
	kt::text::TextEntity text(font);
	text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

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

		// FPS tracking in Debug configuration
#ifdef _DEBUG
		std::cout << elapsedTime.asMilliseconds() << "\n";
#endif

		// Checking for window events
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) window.close();
		}

		// Handle TextEntity
		unsigned int fontSize = 44;
		text.setCharacterSize(fontSize);
		text.setFillColor(sf::Color::White);



		// Track relative mouse position in window
		sf::Vector2i mouseLocalPosition = sf::Mouse::getPosition(window);
		text.setVelocity(sf::Vector2f{ 1.0f, 1.0f });
		
		// Handles text going out of bounds
		text.move(text.getVelocity());

		sf::FloatRect boundingBox = text.getGlobalBounds();
		boundingBox.position.x;

		// Set text string
		std::string textContent;
		//textContent = std::to_string(mouseLocalPosition.x) + " " + std::to_string(mouseLocalPosition.y);
		textContent = std::to_string(boundingBox.position.x) + " " + std::to_string(boundingBox.position.y);
		text.setString(textContent);

		// DEBUG
#if _DEBUG
		std::cout << std::to_string(mouseLocalPosition.x) + " " + std::to_string(mouseLocalPosition.y) << std::endl;

		std::cout << std::to_string(text.getOrigin().x) + " " + std::to_string(text.getOrigin().y) << std::endl;
#endif

		// Clearing old frame from display
		window.clear();

		// Drawing text
		window.draw(text);

		// Finally display drawn objects
		window.display();

		// FPS cap
		sf::Time sleepTime = sf::seconds(TIMESTEP) - clock.restart();
		if (sleepTime.asSeconds() > 0)
		{
			sf::sleep(sleepTime);
		}
	}
}
