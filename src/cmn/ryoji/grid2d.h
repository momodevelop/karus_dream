#ifndef __RYOJI_GRID2D_H__
#define __RYOJI_GRID2D_H__

#include <vector>

namespace ryoji::grid {
	// useful class for a physical 2d grid
	template<typename Tile, typename DimensionType = float>
	class Grid2D {
	public:
		bool init(size_t row, size_t col) {
			grid.resize(row * col);
			return true;
		}

		inline Tile& operator[](size_t index) {
			return grid[index];
		}

		inline const Tile& operator[](size_t index) const {
			return grid[index];
		}

		inline Tile& at(size_t x, size_t y) {
			return grid[x + cols * y]
		}

		inline Tile& at(size_t x, size_t y) const {
			return grid[x + cols * y];
		}

		inline size_t getRows() const { return rows; }
		inline size_t getColumns() const { return cols; }
		inline DimensionType getWidth() const { return tileWidth * cols; }
		inline DimensionType getHeight() const { return tileHeight * rows; }
		inline DimensionType getTileWidth() const { return tileWidth; }
		inline DimensionType getTileHeight() const { return tileHeight; }
		inline DimensionType getTilePosX(size_t x) const { return this->x + x * tileWidth; }
		inline DimensionType getTilePosY(size_t y) const { return this->y + y * tileHeight; }

	public:
		// public variables, can get/set freely
		DimensionType x, y;
		DimensionType tileWidth, tileHeight;

	private:
		std::vector<Tile> grid;
		size_t rows, cols;

	};

}
#endif