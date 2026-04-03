#include "CoreSimulation.h"

namespace kt::Core {
	CoreSimulation::CoreSimulation() {};
	bool CoreSimulation::initialize() {
		window = sf::RenderWindow(sf::VideoMode(windowBounds), CONFIG_MODE);

		std::default_random_engine rng;
		std::uniform_real_distribution<double> rngDistribution(1, kt::Defaults::WINDOW_HEIGHT);

		// Getting font from file
		if (!font.openFromFile(kt::Defaults::FONT_DIR)) {
			std::cout << "ERROR: Font not found at path " << kt::Defaults::FONT_DIR << "\n";
			return false;
		}
		else {
			std::cout << "SUCCESS: Font found at path: " << kt::Defaults::FONT_DIR << "\n";
		}

		font.setSmooth(true);

		// Creating text from font
		movingText = new kt::Text::TextEntity(font);
		movingText->setFont(font);
		unsigned int fontSize = 24;
		movingText->setPosition(sf::Vector2f(kt::Defaults::WINDOW_WIDTH / 2, kt::Defaults::WINDOW_HEIGHT / 2));
		movingText->setCharacterSize(fontSize);
		sf::Color grey(255, 255, 255, 60);
		movingText->setFillColor(grey);
		movingText->setVelocity(sf::Vector2f{ 1.0f, 1.0f });

		cornerText = new kt::Text::TextEntity(font);
		cornerText->setFont(font);
		cornerText->setCharacterSize(fontSize);
		cornerText->setFillColor(sf::Color::White);

		// Creating custom circle
		float posX = (float)rngDistribution(rng);
		float posY = (float)rngDistribution(rng);
		circle.setPosition(sf::Vector2f(posX, posY));

		return true;
	}
	bool CoreSimulation::run() {
		while (window.isOpen()) {
			// Restarting time counter for FPS
			elapsedTime = sf::seconds(0);
			iterationTime = clock.restart();
			elapsedTime += iterationTime;

			// Checking for window events
			while (const std::optional event = window.pollEvent()) {
				if (event->is<sf::Event::Closed>()) window.close();
			}

			// Track relative mouse position in window
			sf::Vector2i mouseLocalPosition = sf::Mouse::getPosition(window);

			// Set text string
			std::string textContent;
			sf::FloatRect boundingBox = movingText->getGlobalBounds();
			textContent = std::to_string(boundingBox.position.x) + ", " + std::to_string(boundingBox.position.y);
			movingText->setString(textContent);
			textContent = std::to_string(mouseLocalPosition.x) + ", " + std::to_string(mouseLocalPosition.y);
			cornerText->setString(textContent);

			//circle.setPosition(sf::Vector2f(boundingBox.position.x, boundingBox.position.y));

			// Handle mouse click
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				if (circle.contains(mouseLocalPosition)) {
					std::cout << "yep" << std::endl;
				}
				else {
					std::cout << "nop" << std::endl;
				}
			}

			// Handle text movement
			//text.move(text.getVelocity());

			this->drawScreen();

			
		}
		return true;
	}

	bool CoreSimulation::exitSimulation() {
		this->deletePointers();
		return true;
	}

	void CoreSimulation::drawScreen() {
		if (!window.isOpen()) {
			return;
		}
		// Clearing old frame from display
		window.clear();

		// Draw circle
		window.draw(circle);

		// Drawing text
		window.draw(*movingText);

		window.draw(*cornerText);

		// Finally display drawn objects
		window.display();
	}

	void CoreSimulation::capFPS() {
		// FPS cap
		sf::Time sleepTime = sf::seconds(kt::Defaults::TIMESTEP) - clock.restart();
		if (sleepTime.asSeconds() > 0)
		{
			sf::sleep(sleepTime);
		}
	}

	void CoreSimulation::deletePointers() {
		delete cornerText;
		delete movingText;
		return;
	}

	CoreSimulation::~CoreSimulation() {};
}