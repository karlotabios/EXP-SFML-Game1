#pragma once

#include <string>

namespace kt::Utils {
	template<typename... T>
	inline void printLog(const std::string& message, const T&... args) {
		static_assert(((std::is_arithmetic_v<T> || std::is_same_v<T, bool> || std::is_same_v<T, std::string>) && ...), "Cannot print non-arithmetic, non-boolean types, or non-standard library string types");

		std::cout << message;

		(std::cout << ... << args) << "\n";

		return;
	}

	// void printLog(const std::string&, const float&);

	void printLog(const std::string&);

	void printException(const std::exception&);
}