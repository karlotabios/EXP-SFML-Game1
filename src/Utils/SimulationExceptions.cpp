#include "SimulationExceptions.h"

namespace kt::Utils {
	SimulationException::SimulationException(const std::string& m) : m_Message{ m } {};

	const char* SimulationException::what() const noexcept {
		return m_Message.c_str();
	}

	SimulationException::~SimulationException() {};
}