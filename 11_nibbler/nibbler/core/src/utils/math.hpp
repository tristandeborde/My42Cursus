#ifndef MATH_HPP
#define	MATH_HPP

#include <type_traits>
#include <cmath>

template <typename T>
T my_abs(const T &value) {
	if (std::is_floating_point<T>::value) {
		return std::fabs(value);
	}
	return std::abs(value);
}

#endif	// MATH_HPP
