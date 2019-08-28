#ifndef __SHARED_GRID_H__
#define __SHARED_GRID_H__

#include <vector>
#include <ryoji/grid2d.h>

namespace app::game::shared {
	struct Tile {
		int value;
	};
	using sharedGrid = ryoji::grid::Grid2D<Tile>;
}

#endif 