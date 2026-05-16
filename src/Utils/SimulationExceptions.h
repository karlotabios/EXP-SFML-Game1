#pragma once

#include <exception>

#include <string>

#include "Frametime.h"

namespace kt::Utils {
	class SimulationException : public std::exception {
	private:
		const std::string m_ExceptionName{"SimulationException"};
		std::string m_Message{};
		const Frametime m_frameData{};

	public:
		// If this were C++23, I would implement std::stacktrace in this class
		// Instead, this will have to do for now in C++17
		struct ErrorSite {
			const int line;
			const std::string file;
		};

		SimulationException() = delete;
		SimulationException(const ErrorSite&, const Frametime&, const std::string& _message = "Unknown simulation exception");
		SimulationException(const SimulationException&) = default;

		const char* what() const noexcept override;
		const std::string getExceptionName() const noexcept;

		virtual ~SimulationException();
	};
}