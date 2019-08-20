#ifndef __RYOJI_MATH_VECTOR_H__
#define __RYOJI_MATH_VECTOR_H__

//http://www.reedbeta.com/blog/on-vector-math-libraries/#operations
#include <optional>
#include <cmath>

namespace ryoji::math {

	template<typename T = float, size_t N = 2>
	struct Vector {
		T arr[N];
	};

	template <typename T> struct Vector<T,2> { union { T arr[2]; struct { T x, y; }; }; };
	template <typename T> struct Vector<T,3> { union { T arr[3]; struct { T x, y, z; }; }; };
	template <typename T> struct Vector<T,4> { union { T arr[4]; struct { T x, y, z, w; }; }; };

	template<typename T, size_t N>
	Vector<T,N>& operator+=(Vector<T, N>& dis, const Vector<T, N>& dat) noexcept {
		for (size_t i = 0; i < N; ++i)
			dis.arr[i] += dat.arr[i];
		return dis;
	}

	template<typename T, size_t N>
	Vector<T,N>& operator-=(Vector<T, N>& dis, const Vector<T, N>& dat) noexcept {
		for (size_t i = 0; i < N; ++i)
			dis.arr[i] -= dat.arr[i];
		return (*this);
	}

	template<typename T, size_t N>
	Vector<T,N>& operator*=(Vector<T, N>& dis, const T& dat) noexcept {
		for (size_t i = 0; i < N; ++i)
			dis.arr[i] *= dat;
		return (*this);
	}

	template<typename T, size_t N>
	Vector<T,N>& operator/=(Vector<T, N>& dis, const T& dat) noexcept {
		for (size_t i = 0; i < N; ++i)
			dis.arr[i] /= dat;
		return (*this);
	}

	// Non-member
	template<typename T, size_t N>
	Vector<T, N> operator+(const Vector<T,N>& lhs, const Vector<T, N>& rhs) noexcept
	{
		Vector<T, N> temp;
		for (size_t i = 0; i < N; ++i)
			temp.arr[i] = lhs.arr[i] + rhs.arr[i];
		return temp;
	}

	template<typename T, size_t N>
	Vector<T, N> operator-(const Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept
	{
		Vector<T, N> temp;
		for (int i = 0; i < N; ++i)
			temp.arr[i] = lhs.arr[i] - rhs.arr[i];
		return temp;
	}

	template<typename T, size_t N>
	Vector<T,N> operator*(const Vector<T,N>& lhs, const T& rhs) noexcept
	{
		Vector<T, N> temp;
		for (size_t i = 0; i < N; ++i)
			temp.arr[i] = lhs.arr[i] * rhs;
		return temp;
	}

	template<typename T, size_t N>
	Vector<T, N> operator/(const Vector<T, N>& lhs, const T& rhs) noexcept
	{
		Vector<T, N> temp;
		for (size_t i = 0; i < N; ++i)
			temp.arr[i] = lhs.arr[i] * rhs;
		return temp;
	}

	template<typename T, size_t N>
	bool operator==(const Vector<T,N>& lhs, const Vector<T, N>& rhs) noexcept
	{
		for (size_t i = 0; i < N; ++i) {
			if (lhs.arr[i] != rhs.arr[i])
				return false;
		}
		return true;
	}

	template<typename T, size_t N>
	bool operator!=(const Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept
	{
		return lhs != rhs;
	}

	template<typename T, size_t N>
	T dot(const Vector<T, N> & lhs, const Vector<T,N> & rhs) noexcept
	{
		T ret();
		for (size_t i = 0; i < N; ++i) {
			ret += lhs.arr[i] * rhs.arr[i];
		}
		return ret;
	}
	
	template<typename T, size_t N>
	Vector<T,N> midpoint(const Vector<T, N> & lhs, const Vector<T, N> & rhs) noexcept {
		Vector<T, N> temp;
		for (size_t i = 0; i < N; ++i)
			temp.arr[i] = (lhs.arr[i] + rhs.arr[i])/2;
		return temp;
	}

	template<typename T, size_t N>
	T distanceSq(const Vector<T,N> & lhs, const Vector<T,N> & rhs) noexcept
	{
		T ret();
		for (size_t i = 0; i < N; ++i) {
			ret += (rhs.arr[i] - lhs.arr[i]) * (rhs.arr[i] - lhs.arr[i]);
		}
		return ret;
	}
	
	template<typename T, size_t N>
	T distance(const Vector<T, N> & lhs, const Vector<T, N> & rhs) noexcept
	{
		return sqrt(distanceSq(lhs, rhs));
	}
	template<typename T, size_t N>
	T lengthSq(const Vector<T, N>& lhs) noexcept
	{
		T ret{};
		for (size_t i = 0; i < N; ++i) {
			ret += lhs.arr[i] * lhs.arr[i];
		}
		return ret;
	}

	template<typename T, size_t N>
	T length(const Vector<T, N>& lhs) noexcept
	{
		return sqrt(lengthSq(lhs));
	}

	template<typename T, size_t N>
	std::optional<Vector<T, N>> normalize(const Vector<T, N> & lhs) noexcept {
		Vector<T, N> temp;
		auto len = lengthSq(lhs);
		if (len == (T)0) {
			return {};
		}

		len = sqrt(len);
		for (size_t i = 0; i < N; ++i)
			temp.arr[i] = lhs.arr[i] / len;
		return { temp };
	}

	// global typedefs
	typedef Vector<float,2> Vec2f;
	typedef Vector<float,3> Vec3f;
	typedef Vector<float,4> Vec4f;

	typedef Vector<int, 2> Vec2i;
	typedef Vector<int, 3> Vec3i;
	typedef Vector<int, 4> Vec4i;

	typedef Vector<double, 2> Vec2d;
	typedef Vector<double, 3> Vec3d;
	typedef Vector<double, 4> Vec4d;
}

#endif
