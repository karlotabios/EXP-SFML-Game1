#include "print.h"
#include "../Globals/color.h"

#include <iostream>

namespace kt::Utils {
	void printLog(const std::string& message) {
		std::cout << message << "\n";
		
		return;
	}

	void printException(const std::exception& e) noexcept {
		std::cerr << kt::Globals::LOG_RED_COLOR << "[EXCEPTION] Exception caught: " << e.what() << "\n" << kt::Globals::LOG_DEFAULT_COLOR;

		return;
	}
}