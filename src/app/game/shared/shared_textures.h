#ifndef __APP_GAME_SHARED_TEXTURES_H__
#define __APP_GAME_SHARED_TEXTURES_H__


#include <yuu/texture_manager.h>
#include <yuu/spritesheet_manager.h>
#include "../types.h"

namespace app::game::shared {
	using SharedTextures = yuu::TextureManager<TextureHandler>;
	using SharedSpritesheets = yuu::SpritesheetManager<SpritesheetHandler>;
}

#endif
