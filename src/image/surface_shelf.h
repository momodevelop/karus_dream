#ifndef __IMAGE_SURFACE_SHELF_H__
#define __IMAGE_SURFACE_SHELF_H__

#include <cassert>
#include "SDL_image.h"

namespace image {

	// Simple class that wraps an array of SDL_Surfaces
	// 
	template<size_t Size>
	class SurfaceShelf {
		SDL_Surface * surfaces[Size]; 

		SurfaceShelf(const SurfaceShelf&) = delete;
		SurfaceShelf& operator=(const SurfaceShelf&) = delete;
	public:
		SurfaceShelf() noexcept;
		virtual ~SurfaceShelf() noexcept;

		bool load(size_t index, const char * path) noexcept;
		void unload(size_t index) noexcept;
		void unloadAll() noexcept;

		SDL_Surface * operator[](size_t index) noexcept;
		const SDL_Surface * operator[](size_t index) const noexcept;
	};


	template<size_t Size>
	inline SurfaceShelf<Size>::SurfaceShelf() noexcept
	{
		for (size_t i = 0; i < Size; ++i) {
			surfaces[i] = nullptr;
		}
	}

	template<size_t Size>
	inline SurfaceShelf<Size>::~SurfaceShelf() noexcept
	{
		for (size_t i = 0; i < Size; ++i) {
			unload(i);
		}
	}

	template<size_t Size>
	inline bool SurfaceShelf<Size>::load(size_t index, const char * path) noexcept
	{
		assert(index >= 0 && index < Size);
		surfaces[index] = IMG_Load(path);
		if (surfaces[index] == nullptr) // failed
			return false;
		return true;
	}
	template<size_t Size>
	inline void SurfaceShelf<Size>::unload(size_t index) noexcept
	{
		assert(index >= 0 && index < Size);
		if (surfaces[index] != nullptr)
			SDL_FreeSurface(surfaces[index]);
	}
	template<size_t Size>
	inline void SurfaceShelf<Size>::unloadAll() noexcept
	{
		for (size_t index = 0; index < Size; ++index) {
			unload(index);
		}
	}
	template<size_t Size>
	inline SDL_Surface * SurfaceShelf<Size>::operator[](size_t index) noexcept
	{
		assert(index >= 0 && index < Size);
		return surfaces[index];
	}
	template<size_t Size>
	inline const SDL_Surface * SurfaceShelf<Size>::operator[](size_t index) const noexcept 
	{
		assert(index >= 0 && index < Size);
		return surfaces[index];
	}
}


#endif