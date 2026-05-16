#include "print.h"
#include "../Globals/color.h"

#include <iostream>

namespace kt::Utils {
	void printError(const std::string& message) {
		std::cerr << kt::Globals::LOG_RED_COLOR << message << kt::Globals::LOG_DEFAULT_COLOR << "\n";

		return;
	}

	void printLog(const std::string& message) {
		std::cout << message << "\n";
		
		return;
	}

	void printException(const std::exception& e) noexcept {
		std::cerr << kt::Globals::LOG_RED_COLOR << "[EXCEPTION] std::exception type caught: " << e.what() << kt::Globals::LOG_DEFAULT_COLOR << "\n";

		return;
	}

	void printException(const kt::Utils::SimulationException& e) noexcept {
		std::cerr << kt::Globals::LOG_RED_COLOR << "[EXCEPTION] " << e.getExceptionName() << " type caught: " << e.what() << kt::Globals::LOG_DEFAULT_COLOR << "\n";

		return;
	}
}