#include <iostream>
#include <SFML/Graphics.hpp>

#define FPS 60.0f
#define TIMESTEP (1.0f / FPS)

int main()
{
	// Window objects
	sf::RenderWindow window( sf::VideoMode( { 200, 200 } ), "SFML works!" );
	sf::CircleShape shape( 100.f );
	shape.setFillColor( sf::Color::Green );

	// Time tracking objects
	sf::Clock clock;
	sf::Time elapsedTime;
	sf::Time iterationTime;

	while ( window.isOpen() )
	{
		std::cout << elapsedTime.asMilliseconds() << "\n";
		elapsedTime = sf::seconds(0);
		iterationTime = clock.restart();
		elapsedTime += iterationTime;

		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		window.clear();
		window.draw( shape );
		window.display();

		sf::Time sleepTime = sf::seconds(TIMESTEP) - clock.restart();
		if (sleepTime.asSeconds() > 0)
		{
			sf::sleep(sleepTime);
		}
	}
}
