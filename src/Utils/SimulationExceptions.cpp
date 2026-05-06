#include "SimulationExceptions.h"

namespace kt::Utils {
	SimulationException::SimulationException(const std::string& _message, const Frametime& _frametime) : m_Message{ _message }, m_frameData { _frametime } {
		m_Message += ".\nTotal Time: " + std::to_string(m_frameData.totalTime.asSeconds()) + " seconds, Frame number: " + std::to_string(m_frameData.frameCounter);
	};

	const char* SimulationException::what() const noexcept {		
		return m_Message.c_str();
	}

	const Frametime& SimulationException::getFrametime() const noexcept {
		return m_frameData;
	}

	SimulationException::~SimulationException() {};
}