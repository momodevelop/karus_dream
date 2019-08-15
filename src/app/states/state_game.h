#ifndef __APP_STATE_GAME_H__
#define __APP_STATE_GAME_H__

#include <SDL.h>
#include <constants.h>
#include <entt.h>
#include <yuu/texture_shelf.h>

#include "state_base.h"
#include "../game/systems/sys_renderer.h"
#include "../game/systems/sys_animator.h"
#include "../game/systems/sys_player_input.h"


namespace app {
	// Forward declarations
	class Root;
	class StateGame : public StateBase {
	public:
		enum TextureEnum {
			TEXTURE_KARU_SPRITESHEET,
			TEXTURE_GRID_SPRITESHEET,
			TEXTURE_MAX
		};
		constexpr static int kMaxEntities = 10;
		
	private: // typedefs
		using texture_shelf_t = yuu::TextureShelf<TEXTURE_MAX>;
	private:
		entt::registry ecs;
		game::systems::SysRenderer sysRenderer;
		game::systems::SysAnimator sysAnimator;
		game::systems::SysPlayerInput sysInput;


		texture_shelf_t textureShelf;

	private:
		StateGame(const StateGame&) = delete;
		StateGame& operator=(const StateGame&) = delete;
		
	public:
		StateGame(SDL_Renderer& renderer);
		~StateGame();

		virtual void onEnter() noexcept override;
		virtual void onUpdate(float dt) noexcept override;
		virtual void onExit() noexcept override;
		virtual void onRender(SDL_Renderer& renderer) noexcept override;
		virtual void onHandleEvent(SDL_Event& e) noexcept override;
		virtual void onClean() noexcept override; 

	};


}
#endif