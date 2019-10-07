#ifndef VECTOR2_HPP
#define	VECTOR2_HPP

#include <utility>
#include <limits>
#include <ostream>

#include "utils/math.hpp"

template <typename T>
class Vector2
{
	/* Instantiation **************************************************************/
	public:
		Vector2(void) : x(static_cast<T>(0)), y(static_cast<T>(0)) {}

		Vector2(T X, T Y) : x(X), y(Y) {}

		~Vector2() = default;

		Vector2(const Vector2& v) : x(v.x), y(v.y)
		{}

		Vector2(Vector2 &&v) noexcept : x(v.x), y(v.y)
		{}

		Vector2		&operator=(const Vector2& v) {
			x = v.x;
			y = v.y;
			return *this;
		}

		Vector2&	operator=(Vector2 &&v) noexcept {
			std::swap(x, v.x);
			std::swap(y, v.y);

			return *this;
		}

	/* Vector methods *************************************************************/
	public:
		template <typename U>
		explicit operator Vector2<U>() const{
			return Vector2<U>(static_cast<U>(x), static_cast<U>(y));
		}

		Vector2 operator*(T v) const{
			return Vector2(x * v, y * v);
		}

		Vector2 operator*(Vector2 v) const{
			return Vector2(x * v.x, y * v.y);
		}

		Vector2	operator+(const Vector2& v) const{
			return Vector2(x + v.x, y + v.y);
		}

		Vector2	operator-(const Vector2& v) const{
			return Vector2(x - v.x, y - v.y);
		}

		bool operator==(T v) const{
			return (x == v && y == v);
		}

		bool operator==(const Vector2& v) const{
			return (my_abs(x - v.x) <= std::numeric_limits<T>::epsilon() &&
				   my_abs(y - v.y) <= std::numeric_limits<T>::epsilon());
		}

		bool operator!=(T v) const{
			return !this->operator==(v);
		}

		bool operator!=(const Vector2& v) const{
			return !this->operator==(v);
		}

		void operator+=(const Vector2& v) {
			x += v.x;
			y += v.y;
		}

		float norm(void) const{
			return (std::sqrt(x * x + y * y));
		}

	/* Attributes *****************************************************************/
	public:
		T x;
		T y;
};

/* Typedefs *******************************************************************/
using Vector2f = Vector2<float>;

/* Operation methods **********************************************************/
template <typename T>
Vector2<T>		abs(const Vector2<T> & vec) {
	return Vector2<T>(my_abs(vec.x), my_abs(vec.y));
}

template <typename T>
std::ostream		&operator<<(std::ostream &os, const Vector2<T> & vec) {
	os << "Vector (" << vec.x << ", " << vec.y << ")";
	return (os);
}

#endif	// VECTOR2_HPP
