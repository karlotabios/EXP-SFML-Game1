#pragma once

#include <string>

namespace kt::Utils {
	template <typename T>
	void printLog(const std::string& message, const T& variable) {
		static_assert(std::is_arithmetic_v<T>, "Cannot print non-arithmetic type");

		std::cout << message << variable << "\n";

		return;
	}

	// void printLog(const std::string&, const float&);

	void printLog(const std::string&);
}