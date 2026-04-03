#include "CoreSimulation.h"

namespace kt::Core {
	CoreSimulation::CoreSimulation() {};
	bool CoreSimulation::initialize() {
		m_window = sf::RenderWindow(sf::VideoMode(m_windowBounds), CONFIG_MODE);

		std::default_random_engine rng;
		std::uniform_real_distribution<double> rngDistribution(1, kt::Defaults::WINDOW_HEIGHT);

		// Getting font from file
		if (!m_font.openFromFile(kt::Defaults::FONT_DIR)) {
			std::cout << "ERROR: Font not found at path " << kt::Defaults::FONT_DIR << "\n";
			return false;
		}
		else {
			std::cout << "SUCCESS: Font found at path: " << kt::Defaults::FONT_DIR << "\n";
		}

		m_font.setSmooth(true);

		// Creating text from font
		m_movingText = new kt::Text::TextEntity(m_font);
		m_movingText->setFont(m_font);
		unsigned int fontSize = 24;
		m_movingText->setPosition(sf::Vector2f(kt::Defaults::WINDOW_WIDTH / 2, kt::Defaults::WINDOW_HEIGHT / 2));
		m_movingText->setCharacterSize(fontSize);
		sf::Color grey(255, 255, 255, 60);
		m_movingText->setFillColor(grey);
		m_movingText->setVelocity(sf::Vector2f{ 1.0f, 1.0f });

		m_cornerText = new kt::Text::TextEntity(m_font);
		m_cornerText->setFont(m_font);
		m_cornerText->setCharacterSize(fontSize);
		m_cornerText->setFillColor(sf::Color::White);

		// Creating custom circle
		float posX = (float)rngDistribution(rng);
		float posY = (float)rngDistribution(rng);
		m_circle.setPosition(sf::Vector2f(posX, posY));

		return true;
	}
	bool CoreSimulation::run() {
		while (m_window.isOpen()) {
			// Restarting time counter for FPS
			m_elapsedTime = sf::seconds(0);
			m_iterationTime = m_clock.restart();
			m_elapsedTime += m_iterationTime;

			// Checking for window events
			while (const std::optional event = m_window.pollEvent()) {
				if (event->is<sf::Event::Closed>()) m_window.close();
			}

			// Track relative mouse position in window
			sf::Vector2i mouseLocalPosition = sf::Mouse::getPosition(m_window);

			// Set text string
			std::string textContent;
			sf::FloatRect boundingBox = m_movingText->getGlobalBounds();
			textContent = std::to_string(boundingBox.position.x) + ", " + std::to_string(boundingBox.position.y);
			m_movingText->setString(textContent);
			textContent = std::to_string(mouseLocalPosition.x) + ", " + std::to_string(mouseLocalPosition.y);
			m_cornerText->setString(textContent);

			//circle.setPosition(sf::Vector2f(boundingBox.position.x, boundingBox.position.y));

			// Handle mouse click
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				if (m_circle.contains(mouseLocalPosition)) {
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
		this->deleteAllPointers();
		return true;
	}

	void CoreSimulation::drawScreen() {
		if (!m_window.isOpen()) {
			return;
		}
		// Clearing old frame from display
		m_window.clear();

		// Draw circle
		m_window.draw(m_circle);

		// Drawing text
		m_window.draw(*m_movingText);

		m_window.draw(*m_cornerText);

		// Finally display drawn objects
		m_window.display();
	}

	void CoreSimulation::capFPS() {
		// FPS cap
		sf::Time sleepTime = sf::seconds(kt::Defaults::TIMESTEP) - m_clock.restart();
		if (sleepTime.asSeconds() > 0)
		{
			sf::sleep(sleepTime);
		}
	}

	void CoreSimulation::deleteAllPointers() {
		delete m_cornerText;
		delete m_movingText;
		return;
	}

	CoreSimulation::~CoreSimulation() {};
}