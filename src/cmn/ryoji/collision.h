#ifndef __RYOJI_COLLISION_H__
#define __RYOJI_COLLISION_H__

#include <ryoji/vector.h>
#include <ryoji/rect.h>

// simple code for detecting collision in 2D
namespace ryoji::collision {
	// checks of two lines are colliding
	template<typename T>
	bool isLinesColliding(T lhsLineMin, T lhsLineMax, T rhsLineMin, T rhsLineMax) {
		if (lhsLineMax >= rhsLineMin) return true;
		if (lhsLineMin <= rhsLineMax) return true;
		return false;
	}

	// Returns the amount of overlap between two lines. 
	// Amount returned is relative to bLine. 
	// Negative amount means aLine is to the left of bLineMin
	// It will return the shortest distance to push out
	template<typename T>
	T getLinesOverlapPushoutAmount(T aLineMin, T aLineMax, T bLineMin, T bLineMax) {
		float checkL = aLineMax - bLineMin;
		float checkR = bLineMax - aLineMin;

		// left is smaller, so return left
		if (checkL < checkR)
			return -checkL;
		else
			return checkR;
	}



}

#endif