#include "CoreSimulation.h"

namespace kt::Core {
	CoreSimulation::CoreSimulation() {};

	bool CoreSimulation::initialize() {
		sf::ContextSettings settings{};
		settings.antiAliasingLevel = kt::Defaults::ANTI_ALIASING_LEVEL;

		m_window = sf::RenderWindow(sf::VideoMode(m_windowBounds), CONFIG_MODE, sf::Style::Default, sf::State::Windowed, settings);

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
		m_movingText.setFont(m_font);
		unsigned int fontSize = 24;
		m_movingText.setPosition(sf::Vector2f(kt::Defaults::WINDOW_WIDTH / 2, kt::Defaults::WINDOW_HEIGHT / 2));
		m_movingText.setCharacterSize(fontSize);
		sf::Color grey(255, 255, 255, 60);	// R,G,B,Alpha
		m_movingText.setFillColor(grey);
		m_movingText.setVelocity(sf::Vector2f{ 1.0f, 1.0f });

		m_cornerText.setFont(m_font);
		m_cornerText.setCharacterSize(fontSize);
		m_cornerText.setFillColor(sf::Color::White);

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
			sf::FloatRect boundingBox = m_movingText.getGlobalBounds();
			textContent = std::to_string(boundingBox.position.x) + ", " + std::to_string(boundingBox.position.y);
			m_movingText.setString(textContent);
			textContent = std::to_string(mouseLocalPosition.x) + ", " + std::to_string(mouseLocalPosition.y);
			m_cornerText.setString(textContent);

			//circle.setPosition(sf::Vector2f(boundingBox.position.x, boundingBox.position.y));

			// Handle keyboard presses
			this->handleKeyboardInput();

			// Handle mouse click
			this->handleMouseInput();

			// Handle object movement
			this->handleObjectMovement();

			this->drawScreen();

			this->capFPS();

			std::system("cls");
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
		m_window.draw(m_movingText);

		m_window.draw(m_cornerText);

		// Finally display drawn objects
		m_window.display();
	}

	void CoreSimulation::capFPS() {
		// FPS cap
		sf::Time sleepTime = sf::seconds(kt::Defaults::TIMESTEP) - m_clock.restart();
		if (sleepTime.asSeconds() > 0)	// here, if the tick speed of the game is faster than prescribed (1/FPS, which should be 0.016s if 60 FPS is the cap) then the game calls sleep for the duration of the excess time.
		{
			std::cout << "[INFO] Capping FPS, sleepTime.asSeconds(): " << sleepTime.asSeconds() << std::endl;
			sf::sleep(sleepTime);
		}
	}

	bool CoreSimulation::handleKeyboardInput() {
		bool isKeyPressed = false;
		bool isMoveKeyPressed = false;
		const sf::Keyboard::Key keyUp = sf::Keyboard::Key::W;
		const sf::Keyboard::Key keyLeft = sf::Keyboard::Key::A;
		const sf::Keyboard::Key keyDown = sf::Keyboard::Key::S;
		const sf::Keyboard::Key keyRight = sf::Keyboard::Key::D;
		const sf::Keyboard::Key keyFriction = sf::Keyboard::Key::Space;

		sf::Keyboard::Key keys[] = { keyUp, keyLeft, keyDown, keyRight, keyFriction };

		sf::Vector2f appliedForce{ 0.0f, 0.0f };

		for (sf::Keyboard::Key key : keys) {
			if (sf::Keyboard::isKeyPressed(key)) {
				isKeyPressed = true;
				
				switch (key) {
				case keyUp:
					isMoveKeyPressed = true;
					appliedForce.y += -kt::Defaults::PLAYER_MOVEMENT_FORCE.y;
					break;
				case keyDown:
					isMoveKeyPressed = true;
					appliedForce.y += kt::Defaults::PLAYER_MOVEMENT_FORCE.y;
					break;
				case keyLeft:
					isMoveKeyPressed = true;
					appliedForce.x += -kt::Defaults::PLAYER_MOVEMENT_FORCE.x;
					break;
				case keyRight:
					isMoveKeyPressed = true;
					appliedForce.x += kt::Defaults::PLAYER_MOVEMENT_FORCE.x;
					break;
				case keyFriction:
					if (!m_isKeyFrictionPressed) {
						if (!m_isFrictionEnabled) {
							std::cout << "[INFO] Enabled Friction!" << std::endl;
						}
						else {
							std::cout << "[INFO] Disabled Friction!" << std::endl;
						}
						m_isKeyFrictionPressed = true;
						m_isFrictionEnabled = !m_isFrictionEnabled;
					}
					break;
				default:
					break;
				}
			}
		}

		if (isMoveKeyPressed) {
			m_circle.addForce(appliedForce);
		}

		if ((!sf::Keyboard::isKeyPressed(keyFriction)) && (m_isKeyFrictionPressed)) {
			m_isKeyFrictionPressed = false;
		}
		return isKeyPressed;
	}

	bool CoreSimulation::handleMouseInput() {
		sf::Vector2i mouseLocalPosition = sf::Mouse::getPosition(m_window);

		bool isMouseClicked = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			isMouseClicked = true;

			if (m_circle.contains(mouseLocalPosition)) {
				m_circle.setPosition(sf::Vector2f(mouseLocalPosition.x, mouseLocalPosition.y));
				m_circle.setVelocity(sf::Vector2f{ 0.0f, 0.0f });
			}
		}

		return isMouseClicked;
	}

	void CoreSimulation::handleObjectMovement() {
		m_circle.move(m_isFrictionEnabled);

		// Handle collision with screen bounds
		sf::Vector2f position = m_circle.getPosition();
		float radius = m_circle.getRadius();
		float rightEdge = position.x + radius;
		float leftEdge = position.x - radius;
		float topEdge = position.y - radius;
		float bottomEdge = position.y + radius;
		if (rightEdge >= kt::Defaults::WINDOW_WIDTH) {
			m_circle.setVelocity({ -m_circle.getVelocity().x, m_circle.getVelocity().y });
			m_circle.setPosition({ kt::Defaults::WINDOW_WIDTH - radius, m_circle.getPosition().y });
		}
		if (leftEdge <= 0.0f) {
			m_circle.setVelocity({ -m_circle.getVelocity().x, m_circle.getVelocity().y });
			m_circle.setPosition({ radius, m_circle.getPosition().y });
		}
		if (topEdge <= 0.0f) {
			m_circle.setVelocity({ m_circle.getVelocity().x, -m_circle.getVelocity().y });
			m_circle.setPosition({ m_circle.getPosition().x, radius });
		}
		if (bottomEdge >= kt::Defaults::WINDOW_HEIGHT) {
			m_circle.setVelocity({ m_circle.getVelocity().x, -m_circle.getVelocity().y });
			m_circle.setPosition({ m_circle.getPosition().x, kt::Defaults::WINDOW_HEIGHT - radius });
		}

		return;
	}

	void CoreSimulation::deleteAllPointers() {
		return;
	}

	CoreSimulation::~CoreSimulation() {};
}