#ifndef __APP_STATE_GAME_H__
#define __APP_STATE_GAME_H__

#include <SDL.h>
#include <constants.h>
#include <entt.h>
#include <yuu/utils.h>

#include "types.h"

#include "systems/sys_renderer.h"
#include "systems/sys_animator.h"
#include "systems/sys_player_input.h"


#include "../state_base.h"



namespace app::game {
	// Forward declarations
	class Root;
	class State : public StateBase {
	public:

		constexpr static int kMaxEntities = 10;

	private:
		entt::registry ecs;
		systems::SysRenderer sysRenderer;
		systems::SysAnimator sysAnimator;
		systems::SysPlayerInput sysInput;
		texture_resources_t textures;

	private:
		State(const State&) = delete;
		State& operator=(const State&) = delete;
		
	public:
		State(SDL_Renderer& renderer);
		~State();

		virtual void onEnter() noexcept override;
		virtual void onUpdate(float dt) noexcept override;
		virtual void onExit() noexcept override;
		virtual void onRender(SDL_Renderer& renderer) noexcept override;
		virtual void onHandleEvent(SDL_Event& e) noexcept override;
		virtual void onClean() noexcept override; 

	};


}
#endif