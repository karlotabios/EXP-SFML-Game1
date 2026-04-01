#include <iostream>
#include <SFML/Graphics.hpp>

static const float FPS = 60.0f;
static const float TIMESTEP = (1.0f / FPS);
static const std::string FONT_DIR = "../font/Roboto/static/Roboto_Condensed-Black.ttf";

int main()
{
	// Window objects
	sf::RenderWindow window( sf::VideoMode( { 800, 600 } ), "SFML works!" );
	sf::CircleShape shape( 100.f );
	shape.setFillColor( sf::Color::Green );

	const static std::string fontPath = FONT_DIR;
	sf::Font font("../font/Roboto/static/Roboto_Condensed-Black.ttf");
	sf::Text text(font);

	if (!font.openFromFile(fontPath)) {
		std::cout << "ERROR: Font not found at path " << fontPath << "\n";
	}
	else {
		std::cout << "SUCCESS: Font found at path: " << fontPath << "\n";
	}

	// FPS time tracking
	sf::Clock clock;
	sf::Time elapsedTime;
	sf::Time iterationTime;

	while ( window.isOpen() )
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
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		// Clearing old rendering frame from display
		window.clear();

		// Drawing new rendering frame into display
		window.draw( shape );
		window.display();

		// FPS cap
		sf::Time sleepTime = sf::seconds(TIMESTEP) - clock.restart();
		if (sleepTime.asSeconds() > 0)
		{
			sf::sleep(sleepTime);
		}
	}
}
