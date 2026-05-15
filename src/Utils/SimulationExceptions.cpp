#include "SimulationExceptions.h"

namespace kt::Utils {
	SimulationException::SimulationException(const ErrorSite& _lineFile, const Frametime& _frametime, const std::string& _message) : m_Message{ _message }, m_frameData{ _frametime } {
		m_Message += ".\nAt file " 
			+ _lineFile.file 
			+ ":" 
			+ std::to_string(_lineFile.line) 
			+ "\nTotal Time: " 
			+ std::to_string(m_frameData.totalTime.asSeconds()) 
			+ " seconds, Frame number: " 
			+ std::to_string(m_frameData.frameCounter) 
			+ "\n";
	};

	const char* SimulationException::what() const noexcept {
		return m_Message.c_str();
	}

	const Frametime& SimulationException::getFrametime() const noexcept {
		return m_frameData;
	}

	SimulationException::~SimulationException() {};
}