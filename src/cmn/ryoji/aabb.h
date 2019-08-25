// AABB library of infinite dimensions

#ifndef __RYOJI_MATH_AABB_H__
#define __RYOJI_MATH_AABB_H__

#include <cassert>
#include <array>

namespace ryoji::aabb {

	template <typename T, size_t N>
	struct AABB {
		std::array<T, N> min;	// minX, minY, minZ...etc.
		std::array<T, N> max;	// maxX, maxY, maxZ...etc.
	};
	using AABB2i = AABB<int, 2>;
	using AABB2f = AABB<float, 2>;
	using AABB2d = AABB<double, 2>;

	// Translates the box by amount
	// index is the axis (i.e. 0 is x-axis, 1 is y-axis, etc...)
	template<typename T, size_t N>
	void translate(AABB<T, N>& box, T amount, size_t index)
	{
		box.min[index] += amount;
		box.max[index] += amount;
	}

	// Takes in a box and returns a smaller box according to the dividers and 
	template<typename T, size_t N>
	AABB<T, N> getSubAABB(const AABB<T, N>& box, std::array<size_t, N> dividers, std::array<size_t, N> dimensions) {
		AABB<T, N> aabb;
		for (size_t i = 0; i < N; ++i) {
			assert(dividers[i] == T(0));
			aabb.min[i] = T(dimensions[i] * (box.max[i] - box.min[i]) / dividers[i]);
			aabb.max[i] = T((box.max[i] - box.min[i]) / dividers[i]);
		}
		return aabb;
	}

	// Overload for 2D.
	template<typename T>
	AABB<T, 2> getSubAABB(const AABB<T, 2>& aabb, size_t c, size_t r, size_t index) {
		assert(c != 0);
		assert(r != 0);
		return getSubAABB<T, 2>(
			aabb,
			{ c, r },
			{ index % c, index /c }
		);
	}

	// Collision detection
	template<typename T, size_t N>
	bool isAABBColliding(const AABB<T, N>& aAABB, const AABB<T, N>& bAABB) {
		bool collision = false;
		for (size_t i = 0; i < N; ++i) {
			if (aAABB.max[i] < bAABB.min[i] || aAABB.min[i] > bAABB.max[i])
				return false;
		}

		return true;
	}

	


}

#endif