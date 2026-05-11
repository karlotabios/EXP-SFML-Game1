#include "SimulationExceptions.h"

namespace kt::Utils {
	SimulationException::SimulationException(const Frametime& _frametime, const std::string& _message) : m_Message{ _message }, m_frameData{ _frametime } {
		m_Message += ".\nTotal Time: " + std::to_string(m_frameData.totalTime.asSeconds()) + " seconds, Frame number: " + std::to_string(m_frameData.frameCounter);
	};

	/*SimulationException::SimulationException(const Frametime& _frametime, const std::string& _message) : 
		m_Message{ _message },
		m_frameData{ _frametime }, 
		std::exception::exception((_message + ".\nTotal Time: " + std::to_string(_frametime.totalTime.asSeconds()) + " seconds, Frame number: " + std::to_string(_frametime.frameCounter)).c_str()) {
		m_Message += ".\nTotal Time: " + std::to_string(m_frameData.totalTime.asSeconds()) + " seconds, Frame number: " + std::to_string(m_frameData.frameCounter);
	};*/

	/*SimulationException::SimulationException(const SimulationException& _other) : m_Message{ _other.m_Message }, m_frameData{ _other.m_frameData } {};*/

	const char* SimulationException::what() const noexcept {		
		return m_Message.c_str();
	}

	const Frametime& SimulationException::getFrametime() const noexcept {
		return m_frameData;
	}

	SimulationException::~SimulationException() {};
}