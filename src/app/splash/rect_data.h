#ifndef __APP_SPLASH_RECT_DATA_H__
#define __APP_SPLASH_RECT_DATA_H__

#include <SDL.h>
#include <ryoji/vector.h>

#include "types.h"

namespace app::splash {
	class RectData {
		using Vec2f = ryoji::math::Vec2f;
	public:
		Vec2f current;
		Vec2f start;
		Vec2f end;
		Vec2f size;
		TextureHandler textureHandler;
		Uint8 alpha;

		RectData(Vec2f start, Vec2f end, Vec2f size, TextureHandler textureHandler)
			: start(start), end(end), size(size), textureHandler(textureHandler),
			alpha(255), current(start)
		{
		}
	};
}

#endif