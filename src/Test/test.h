#pragma once

#include <exception>

// std::remove_cv_t, std::remove_reference_t
#include <type_traits>

namespace kt::Test {
	// Boolean check whether a type is derived or is exactly of type std::exception
	template <typename T>
	constexpr bool is_std_exception_v = std::is_base_of<std::exception, std::remove_cv_t<std::remove_reference_t<T>>>::value;

	// T requires std::exception or class derived from std::exception
	template<typename T>
	void test(T& except) {
		static_assert(is_std_exception_v<T>, "Argument is not derived from nor a std::exception type");
		throw except;
		return;
	}
}