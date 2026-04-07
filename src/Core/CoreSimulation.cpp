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

			// Handle keyboard presses
			this->handleKeyboardInput();

			// Handle mouse click
			this->handleMouseInput();

			// Handle object movement
			// TODO

			this->drawScreen();

			this->capFPS();
		}
		return true;
	}

	bool CoreSimulation::exitSimulation() {
		this->deleteAllPointers();
		return true;	// WIP, thinking of changing this
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

	bool CoreSimulation::handleKeyboardInput() {
		bool isKeyPressed = false;
		const sf::Keyboard::Key keyUp = sf::Keyboard::Key::W;
		const sf::Keyboard::Key keyLeft = sf::Keyboard::Key::A;
		const sf::Keyboard::Key keyDown = sf::Keyboard::Key::S;
		const sf::Keyboard::Key keyRight = sf::Keyboard::Key::D;

		sf::Keyboard::Key keys[] = { keyUp, keyLeft, keyDown, keyRight };
		
		for (sf::Keyboard::Key key : keys) {
			if (sf::Keyboard::isKeyPressed(key)) {
				isKeyPressed = true;
				std::cout << "[INFO] Keyboard key pressed, enum base type: " << static_cast<int>(key) << std::endl;
				
				float force = m_circle.getMovementForce();
				float mass = m_circle.getMass();
				sf::Vector2f acceleration = m_circle.getAcceleration();

				switch (key) {
				case keyUp:
					acceleration.y -= force / mass;
					break;
				case keyDown:
					acceleration.y += force / mass;
					break;
				case keyLeft:
					acceleration.x -= force / mass;
					break;
				case keyRight:
					acceleration.x += force / mass;
					break;
				default:
					break;
				}
				m_circle.setAcceleration(acceleration);
			}
		}

		return isKeyPressed;
	}

	bool CoreSimulation::handleMouseInput() {
		sf::Vector2i mouseLocalPosition = sf::Mouse::getPosition(m_window);

		bool isMouseClicked = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			if (m_circle.contains(mouseLocalPosition)) {
				m_circle.setPosition(sf::Vector2f(mouseLocalPosition.x, mouseLocalPosition.y));
			}
			else {
				std::cout << "[INFO] Mouse left click pressed, but without interaction" << std::endl;
			}
		}

		return isMouseClicked;
	}

	void CoreSimulation::handleObjectMovement() {
		sf::Vector2f acceleration = m_circle.getAcceleration();
		sf::Vector2f velocity = m_circle.getVelocity();
		velocity += acceleration;
		m_circle.setVelocity(velocity);

		// TODO apply velocity to position
		return;
	}

	void CoreSimulation::deleteAllPointers() {
		delete m_cornerText;
		delete m_movingText;
		return;
	}

	CoreSimulation::~CoreSimulation() {};
}