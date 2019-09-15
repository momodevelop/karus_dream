#ifndef __RYOJI_MATH_COMMON_H__
#define __RYOJI_MATH_COMMON_H__


namespace ryoji::math {

	// Keeps a value within a range
	template<typename T> 
	T clamp(T start, T end, T value) {
		if (value < start)
			return start;
		if (value > end)
			return end;
		return value;
	}

	inline size_t get1dFrom2d(size_t x, size_t y, size_t gridColumns) {
		return x + gridColumns * y;
	}

	template<typename T>
	T pow(T lhs, T rhs) {
		T result = lhs;
		for (size_t i = 0; i < rhs - 1; ++i) {
			result *= lhs;
		}

		return result;
	}
}

#endif