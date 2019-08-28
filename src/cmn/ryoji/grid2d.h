#ifndef __RYOJI_GRID2D_H__
#define __RYOJI_GRID2D_H__

#include <vector>
#include <type_traits>

namespace ryoji::grid {
	// useful class for a physical 2d grid
	template<typename Tile>
	class Grid2D {
	public:
		void init(float x, float y, float tileWidth, float tileHeight, unsigned rows, unsigned cols) {
			grid.clear();
			this->rows = rows;
			this->cols = cols;
			this->x = x;
			this->y = y;
			this->tileHeight = tileHeight;
			this->tileWidth = tileWidth;
			grid.resize(rows * cols);
		}

		inline Tile& operator[](size_t index) {
			return grid[index];
		}

		inline const Tile& operator[](size_t index) const {
			return grid[index];
		}

		inline Tile& at(size_t x, size_t y) {
			return grid[x + cols * y];
		}

		inline Tile& at(size_t x, size_t y) const {
			return grid[x + cols * y];
		}

		inline unsigned getRows() const { return rows; }
		inline unsigned getColumns() const { return cols; }
		inline float getWidth() const { return tileWidth * cols; }
		inline float getHeight() const { return tileHeight * rows; }
		inline float getTileWidth() const { return tileWidth; }
		inline float getTileHeight() const { return tileHeight; }
		inline float getTilePosX(size_t x) const { return this->x + x * tileWidth; }
		inline float getTilePosY(size_t y) const { return this->y + y * tileHeight; }

	public:
		// public variables, can get/set freely
		float x, y;
		float tileWidth, tileHeight;

	protected:
		std::vector<Tile> grid;
		unsigned rows, cols;

	};

}
#endif