#pragma once

#include <exception>

#include <string>

#include "Frametime.h"

namespace kt::Utils {
	class SimulationException : public std::exception {
	private:
		std::string m_Message{};
		Frametime m_frameData{};

	public:
		SimulationException(const std::string&);

		const char* what() const noexcept override;
		// TODO: add stack trace to what() message

		virtual ~SimulationException();
	};
}