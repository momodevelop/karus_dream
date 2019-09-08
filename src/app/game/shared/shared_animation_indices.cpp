#include "shared_animation_indices.h"

namespace app::game::shared {
	bool SharedAnimationIndices::init()
	{
		indicesSet.emplace_back(indices_t{ 1, 0, 1, 2 }); // UP
		indicesSet.emplace_back(indices_t{ 4, 3, 4, 5 }); // DOWN
		indicesSet.emplace_back(indices_t{ 7, 6, 7, 8 }); // LEFT
		indicesSet.emplace_back(indices_t{ 10, 9, 10, 11 }); // RIGHT

		indicesSet.emplace_back(indices_t{ 1 }); // UP_STOP
		indicesSet.emplace_back(indices_t{ 4 }); // DOWN_STOP
		indicesSet.emplace_back(indices_t{ 7 }); // LEFT_STOP
		indicesSet.emplace_back(indices_t{ 10 }); // RIGHT_STOP

		indicesSet.emplace_back(indices_t{ 0, 1, 2, 3, 4, 5 }); // COIN
		return true;
	}

	

}