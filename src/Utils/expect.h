#pragma once

// kt::Utils::SimulationException class
#include "SimulationExceptions.h"

// std::is_invocable, std::is_base_of, std::remove_cv_t, std::reference_t
#include <type_traits>

// kt::Utils::printError() function
#include "print.h"

#include "../Globals/color.h"

namespace kt::Utils {
	// Boolean check whether a type is derived or is exactly of type std::exception
	template <typename T>
	constexpr bool is_std_exception_v = std::is_base_of<std::exception, std::remove_cv_t<std::remove_reference_t<T>>>::value;

	enum class ErrorAction { ActionLog, ActionThrow, ActionTerminate };

	template<ErrorAction defaultThrow = ErrorAction::ActionThrow, typename P, typename T>
	bool expect(P& predicate, const T& except) {
		static_assert(std::is_invocable_v<decltype(predicate)>, "[STATIC_ASSERT FAILURE] Cannot invoke non-function object argument \"P& predicate\". Argument is meant to be a predicate type with call operator.");
		static_assert(is_std_exception_v<T>, "[STATIC_ASSERT FAILURE] \"expect\" function cannot proceed with passed argument. \"const T& except\" argument must be type derived from or exactly std::exception");
		
		bool result{ predicate() };

		if constexpr (defaultThrow == ErrorAction::ActionLog) {
			if (!result) {
				kt::Utils::printError("[EXPECT FAIL] expect() encountered predicate that returned false.");
				kt::Utils::printError(except.what());
			}
		}
		if constexpr (defaultThrow == ErrorAction::ActionThrow) {
			if (!result) {
				throw except;
			}
		}
		if constexpr (defaultThrow == ErrorAction::ActionTerminate) {
			if (!result) {
				std::terminate();
			}
		}

		return result;
	}
}