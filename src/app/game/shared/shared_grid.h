#ifndef __SHARED_GRID_H__
#define __SHARED_GRID_H__

#include <SDL.h>
#include <ryoji/grid2d.h>

namespace app::game::shared {
	struct GridTile {
		int value;
	};
	using SharedGrid = ryoji::grid::Grid2D<GridTile>;

}

#endif 