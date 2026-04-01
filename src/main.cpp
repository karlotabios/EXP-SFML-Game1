#include <iostream>
#include <SFML/Graphics.hpp>
#include "text/text.h"
#include "defaults/defaults.h"


int main()
{
	// Window objects
	sf::RenderWindow window(sf::VideoMode( { 800, 600 } ), "SFML works!");

	// Getting font from file
	sf::Font font(FONT_DIR);

	if (!font.openFromFile(FONT_DIR)) {
		std::cout << "ERROR: Font not found at path " << FONT_DIR << "\n";
	}
	else {
		std::cout << "SUCCESS: Font found at path: " << FONT_DIR << "\n";
	}

	// Creating text from font
	TextEntity text(font);

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

		unsigned int fontSize = 24;
		text.setCharacterSize(fontSize);
		text.setFillColor(sf::Color::White);
		text.setString("Hello World!");
		text.move({1.0f,1.0f});

		sf::Vector2f textVelocity;

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
