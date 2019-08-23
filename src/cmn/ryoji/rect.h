#ifndef __MATH_RECT_H__
#define __MATH_RECT_H__

#include <cassert>
#include "vector.h"

namespace ryoji::math {

	template <typename T>
	struct Rect {
		//T x, y, w, h;
		T minX, minY, maxX, maxY;
	};

	// Give a rectangle's width and height and the rows and columns you want to divide the rectangle by. Also provide an index
	// The return value will be the x/y/w/h of the section on the rectangle based on a 2D index.
	template<typename T>
	Rect<T> getSubRect(const Rect<T>& rect, size_t c, size_t r, size_t x, size_t y) {
		assert(x < c);
		assert(y < r);
		assert(c != 0);
		assert(r != 0);

		return Rect<T>(
			(T)(x * (rect.maxX - rect.minX)/c), 
			(T)(y * (rect.maxY - rect.minY) /r),
			(T)((rect.maxX - rect.minX)/c),
			(T)((rect.maxY - rect.minY)/r));
	}

	// Give a rectangle's width and height and the rows and columns you want to divide the rectangle by. Also provide an index
	// The return value will be the x/y/w/h of the section on the rectangle based on the index.
	template<typename T>
	Rect<T> getSubRect(const Rect<T>& rect, size_t c, size_t r, size_t index) {
		// make sure the index is valid
		assert(c != 0);
		assert(r != 0);

		return getSubRect(rect, c, r, index % c, index / c);
	}


	typedef Rect<int> Recti;
	typedef Rect<float> Rectf;
	typedef Rect<double> Rectd;

}

#endif