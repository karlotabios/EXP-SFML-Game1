#include "print.h"
#include "../Globals/color.h"

#include <iostream>
#include <type_traits>

namespace kt::Utils {
	void printLog(const std::string& message) {
		std::cout << message << "\n";
		
		return;
	}

	void printException(const std::exception& e) {
		std::cerr << "Exception caught: " << e.what() << "\n";

		return;
	}
}