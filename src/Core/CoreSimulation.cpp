#include "CoreSimulation.h"

// kt::Utils::SimulationException Class
#include "../Utils/SimulationExceptions.h"

// kt::Utils::printException()
#include "../Utils/print.h"

// kt::Utils::expect()
#include "../Utils/expect.h"

// Testing C++ features
#include "../Test/test.h"

namespace kt::Core {
	CoreSimulation::CoreSimulation() : m_lagTexture(kt::Globals::LAG_IMAGE_FILE_PATH) {};

	bool CoreSimulation::initialize() {
		sf::ContextSettings settings{};
		settings.antiAliasingLevel = kt::Globals::ANTI_ALIASING_LEVEL;

		m_window = sf::RenderWindow(sf::VideoMode(m_windowBounds), CONFIG_MODE, sf::Style::Default, sf::State::Windowed, settings);

		std::default_random_engine rng;
		std::uniform_real_distribution<double> rngDistribution(1, kt::Globals::WINDOW_HEIGHT);

		// Getting font from file
		if (!m_font.openFromFile(kt::Globals::FONT_FILE_PATH)) {
			std::cout << "ERROR: Font not found at path " << kt::Globals::FONT_FILE_PATH << "\n";
			return false;
		}

		//Initialize UI Icon
		if (!m_lagTexture.loadFromFile(kt::Globals::LAG_IMAGE_FILE_PATH)) {
			std::cout << "ERROR: Image file not found at path " << kt::Globals::LAG_IMAGE_FILE_PATH << "\n";
			return false;
		}
		else {
			m_lagSprite.setTexture(m_lagTexture);
			m_lagSprite.setScale({ 0.2f, 0.2f });
		}

		m_font.setSmooth(true);

		// Creating text from font
		m_movingText.setFont(m_font);
		unsigned int fontSize = 24;
		m_movingText.setPosition(sf::Vector2f(kt::Globals::WINDOW_WIDTH / 2, kt::Globals::WINDOW_HEIGHT / 2));
		m_movingText.setCharacterSize(fontSize);
		sf::Color grey(255, 255, 255, 60);	// R,G,B,Alpha
		m_movingText.setFillColor(grey);
		m_movingText.setVelocity(sf::Vector2f{ 1.0f, 1.0f });

		m_cornerText.setFont(m_font);
		m_cornerText.setCharacterSize(fontSize);
		m_cornerText.setFillColor(sf::Color::White);
		m_cornerText.setPosition({ 0.0f, kt::Globals::WINDOW_HEIGHT - 30.0f });

		// Customizing circle
		float posX = (float)rngDistribution(rng);
		float posY = (float)rngDistribution(rng);
		m_circle.setPosition(sf::Vector2f(posX, posY));

		// Customizing rectangle
		m_rectangle.setPosition(sf::Vector2f{ kt::Globals::WINDOW_WIDTH / 2.0f, kt::Globals::WINDOW_HEIGHT / 2.0f });
		sf::Vector2f size = m_rectangle.getSize();
		size.x = kt::Globals::WINDOW_HEIGHT * 0.1f;
		size.y = kt::Globals::WINDOW_HEIGHT;
		m_rectangle.setSize(size);
		m_rectangle.setOrigin(sf::Vector2f{ size.x / 2.0f, size.y / 2.0f });

		// Customizing geometry
		m_centerVerticalLine.setPosition(sf::Vector2f{ kt::Globals::WINDOW_WIDTH / 2.0f, 0.0f });
		m_centerVerticalLine.setFillColor(sf::Color::White);
		m_centerVerticalLine.setSize(sf::Vector2f{ 1.0f, kt::Globals::WINDOW_HEIGHT });

		m_centerHorizontalLine.setPosition(sf::Vector2f{ 0.0f, kt::Globals::WINDOW_HEIGHT / 2.0f });
		m_centerHorizontalLine.setFillColor(sf::Color::White);
		m_centerHorizontalLine.setSize(sf::Vector2f{ kt::Globals::WINDOW_WIDTH, 1.0f });

		//Initialize deltaTime
		m_Time.deltaTime = sf::seconds(std::max(kt::Globals::TIMESTEP, m_Time.elapsedTime.asSeconds()));

		return true;
	}

	bool CoreSimulation::run() {
		while (m_window.isOpen()) {
			// Checking for window events
			while (const std::optional event = m_window.pollEvent()) {
				if (event->is<sf::Event::Closed>()) m_window.close();
			}

			// Handle input
			this->handleInput();
			
			// Update
			this->update();

			// Draw
			this->drawScreen();

			// Handle update and display frame rate
			this->capUPS();
			this->trackFPS();

			std::system("cls");
		}
		return true;
	}

	void CoreSimulation::update() {
		// Handle Game changes
		this->handleSimulationState();

		// Handle object changes
		this->handleObjectState();

		// Handle object movement
		this->handleObjectMovement();

		// Handle UI
		this->handleUI();

		return;
	}

	void CoreSimulation::drawScreen() {
		if (!m_window.isOpen()) {
			return;
		}
		// Clearing old frame from display
		m_window.clear(backgroundColor);

		// Draw objects
		for (auto& object : m_drawableObjects) {
			m_window.draw(*object);
		}

		// Finally display drawn objects
		m_window.display();
	}

	void CoreSimulation::capUPS() {
		if (m_isLagSpikeEnabled) {
			sf::sleep(sf::seconds(m_lagSeconds));
		}

		// Restarting time counter for FPS
		m_Time.elapsedTime = m_Time.clock.restart();
		sf::Time sleepTime = sf::seconds(kt::Globals::TIMESTEP) - m_Time.elapsedTime;
		m_Time.deltaTime = sf::seconds(std::max(kt::Globals::TIMESTEP, m_Time.elapsedTime.asSeconds()));

		if (sleepTime.asSeconds() > 0)	// here, if the tick speed of the game is faster than prescribed (1/FPS, which should be 0.016s if 60 FPS is the cap) then the game calls sleep for the duration of the excess time.
		{
			sf::sleep(sleepTime);
		}

	}

	void CoreSimulation::trackFPS() {
		// Increment frame counter
		m_Time.frameCounter++;
		m_secondsCounter += m_Time.deltaTime.asSeconds();
		m_Time.totalTime += m_Time.deltaTime;
		float fpsOverTime = m_Time.frameCounter / m_Time.totalTime.asSeconds();
		if (m_secondsCounter >= 1) {
			std::ostringstream oss;
			oss << fpsOverTime;
			m_averageFPSText = oss.str();
			m_secondsCounter = 0;
		}
		std::cout << "[INFO] Total simulation seconds: " << m_Time.totalTime.asSeconds() << std::endl;
		std::cout << "[INFO] Frame count: " << m_Time.frameCounter << std::endl;
		std::cout << "[INFO] Average FPS: " << m_averageFPSText << std::endl;

		try {
			if (m_secondsCounter == 0) {
				kt::Utils::expect(
					[&] { return (fpsOverTime < kt::Globals::FPS); }, 
					kt::Utils::SimulationException(
						kt::Utils::SimulationException::ErrorSite{
							__LINE__,
							__FILE__
						},
						m_Time, 
						"Simulation is running beyond FPS cap " 
							+ std::to_string(kt::Globals::FPS) 
							+ ", running at " 
							+ std::to_string(fpsOverTime)
					)
				);
			}
		}
		catch (const std::exception& e) {
			kt::Utils::printException(e);
			std::terminate();
		}

		return;
	}

	void CoreSimulation::handleInput() {
		this->handleKeyboardInput();
		this->handleMouseInput();
		return;
	}

	void CoreSimulation::handleKeyboardInput() {
		bool isKeyPressed = false;
		bool isMoveKeyPressed = false;

		// List of keys and what they are mapped to on the keyboard
		const sf::Keyboard::Key keyUp = sf::Keyboard::Key::W;
		const sf::Keyboard::Key keyLeft = sf::Keyboard::Key::A;
		const sf::Keyboard::Key keyDown = sf::Keyboard::Key::S;
		const sf::Keyboard::Key keyRight = sf::Keyboard::Key::D;
		const sf::Keyboard::Key keyFriction = sf::Keyboard::Key::Space;
		const sf::Keyboard::Key keyLagSpike = sf::Keyboard::Key::L;

		sf::Keyboard::Key keys[] = { keyUp, keyLeft, keyDown, keyRight, keyFriction, keyLagSpike };

		sf::Vector2f appliedForce{ 0.0f, 0.0f };

		for (sf::Keyboard::Key key : keys) {
			if (sf::Keyboard::isKeyPressed(key)) {
				isKeyPressed = true;
				
				switch (key) {
				case keyUp:
					isMoveKeyPressed = true;
					appliedForce.y += -kt::Globals::PLAYER_MOVEMENT_FORCE.y;
					break;
				case keyDown:
					isMoveKeyPressed = true;
					appliedForce.y += kt::Globals::PLAYER_MOVEMENT_FORCE.y;
					break;
				case keyLeft:
					isMoveKeyPressed = true;
					appliedForce.x += -kt::Globals::PLAYER_MOVEMENT_FORCE.x;
					break;
				case keyRight:
					isMoveKeyPressed = true;
					appliedForce.x += kt::Globals::PLAYER_MOVEMENT_FORCE.x;
					break;
				case keyFriction:
					if (!m_isKeyFrictionPressed) {
						m_isKeyFrictionPressed = true;
						m_isFrictionEnabled = !m_isFrictionEnabled;
					}
					break;
				case keyLagSpike:
					if (!m_isKeyLagSpikePressed) {
						m_isLagSpikeEnabled = !m_isLagSpikeEnabled;
						m_isKeyLagSpikePressed = true;
					}
					break;
				default:
					break;
				}
			}
		}

		std::string message;
		message = m_isLagSpikeEnabled ? "[INFO] Lag Spike Enabled" : "[INFO] Lag Spike Disabled";
		std::cout << message << std::endl;
		message = m_isFrictionEnabled ? "[INFO] Enabled Friction!" : "[INFO] Disabled Friction!";
		std::cout << message << std::endl;

		if (isMoveKeyPressed) {
			m_circle.addForce(appliedForce);
		}

		if ((!sf::Keyboard::isKeyPressed(keyFriction)) && (m_isKeyFrictionPressed)) {
			m_isKeyFrictionPressed = false;
		}

		if (!sf::Keyboard::isKeyPressed(keyLagSpike)) {
			m_isKeyLagSpikePressed = false;
		}
		return;
	}

	void CoreSimulation::handleMouseInput() {
		// Capture mouse position
		sf::Vector2i mouseLocalPosition = sf::Mouse::getPosition(m_window);

		// Check for mouse input
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

			if (m_circle.contains(mouseLocalPosition)) {
				m_circle.setPosition(sf::Vector2f(mouseLocalPosition.x, mouseLocalPosition.y));
				m_circle.setVelocity(sf::Vector2f{ 0.0f, 0.0f });
			}
		}

		return;
	}

	void CoreSimulation::handleObjectMovement() {
		// Apply physics to object
		m_circle.move(m_Time.deltaTime, m_isFrictionEnabled);

		// Handle collision related things
		// TODO: Implementation here

		this->handleObjectOutOfBounds();

		return;
	}

	void CoreSimulation::handleObjectOutOfBounds() {
		// Handle collision with screen bounds
		sf::Vector2f position = m_circle.getPosition();
		float radius = m_circle.getRadius();
		float rightEdge = position.x + radius;
		float leftEdge = position.x - radius;
		float topEdge = position.y - radius;
		float bottomEdge = position.y + radius;
		if (rightEdge >= kt::Globals::WINDOW_WIDTH) {
			m_circle.setVelocity({ -m_circle.getVelocity().x, m_circle.getVelocity().y });
			m_circle.setPosition({ kt::Globals::WINDOW_WIDTH - radius, m_circle.getPosition().y });
		}
		if (leftEdge <= 0.0f) {
			m_circle.setVelocity({ -m_circle.getVelocity().x, m_circle.getVelocity().y });
			m_circle.setPosition({ radius, m_circle.getPosition().y });
		}
		if (topEdge <= 0.0f) {
			m_circle.setVelocity({ m_circle.getVelocity().x, -m_circle.getVelocity().y });
			m_circle.setPosition({ m_circle.getPosition().x, radius });
		}
		if (bottomEdge >= kt::Globals::WINDOW_HEIGHT) {
			m_circle.setVelocity({ m_circle.getVelocity().x, -m_circle.getVelocity().y });
			m_circle.setPosition({ m_circle.getPosition().x, kt::Globals::WINDOW_HEIGHT - radius });
		}

		return;
	}

	void CoreSimulation::handleUI() {
		// Track relative mouse position in window
		sf::Vector2i mouseLocalPosition = sf::Mouse::getPosition(m_window);

		// Set text string
		std::string textContent;
		sf::FloatRect boundingBox = m_movingText.getGlobalBounds();
		textContent = std::to_string(boundingBox.position.x) + ", " + std::to_string(boundingBox.position.y);
		m_movingText.setString(textContent);
		textContent = std::to_string(mouseLocalPosition.x) + ", " + std::to_string(mouseLocalPosition.y);
		m_cornerText.setString(textContent);

		return;
	}

	void CoreSimulation::handleSimulationState() {
		// Temporary repeated handling of states here. TODO: make helper functions to handle this only once every time change happens
		if (m_isFrictionEnabled) {
			backgroundColor = sf::Color::Black;
		}
		else {
			backgroundColor = sf::Color(10U, 30U, 60U, 255U);
		}

		if (m_isLagSpikeEnabled) {
			m_lagSprite.setScale({ 0.2f, 0.2f });
		}
		else {
			m_lagSprite.setScale({ 0.0f, 0.0f });
		}

		return;
	}

	void CoreSimulation::handleObjectState() {
		// Collision detection
		auto collisionData = kt::Utils::detectCollision(m_rectangle, m_circle);
		if (collisionData != std::nullopt) {
			m_circle.makeTransparent();
			sf::Vector2f positionDelta = collisionData->collisionNormalDirection * collisionData->overlapMagnitude;
			sf::Vector2f oldPosition = m_circle.getPosition();
			sf::Vector2f newPosition = m_circle.getPosition() + positionDelta;
			m_circle.setVelocity({ 0.0f,0.0f });	// Temporary workaround
			m_circle.setPosition(newPosition);
		}
		else {
			m_circle.makeOpaque();
		}

		return;
	}

	bool CoreSimulation::exitSimulation() {
		return true;	// WIP, thinking of changing this
	}

	CoreSimulation::~CoreSimulation() {};
}