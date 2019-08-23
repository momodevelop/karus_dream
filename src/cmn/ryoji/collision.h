#ifndef __RYOJI_COLLISION_H__
#define __RYOJI_COLLISION_H__

// simple code for detecting collision in 2D
namespace collision {
	template<typename T>
	bool isLinesColliding(T lhsLineMin, T lhsLineMax, T rhsLineMin, T rhsLineMax) {
		if (lhsLineMax >= rhsLineMin) return true;
		if (lhsLineMin <= rhsLineMax) return true;
		return false;
	}

	template<typename T>
	T getCollidingLinesPushout(T lhsLineMin, T lhsLineMax, T rhsLineMin, T rhsLineMax) {

	}

}

#endif