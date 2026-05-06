#pragma once

#include <exception>

#include <string>

#include "Frametime.h"

namespace kt::Utils {
	class SimulationException : public std::exception {
	private:
		std::string m_Message{};
		const Frametime m_frameData{};

	public:
		SimulationException() = delete;
		SimulationException(const std::string&, const Frametime&);

		const char* what() const noexcept override;
		const Frametime& getFrametime() const noexcept;

		// TODO: add stack trace to what() message

		virtual ~SimulationException();
	};
}