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
}

#endif