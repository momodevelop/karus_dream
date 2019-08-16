#include "../components/com_transform.h"
#include "../components/com_player_input.h"
#include "sys_player_input.h"

namespace app::game::systems {
	using namespace components;
	void SysPlayerInput::handleEvent(entt::registry& registry, SDL_Event& e) {
		auto view = registry.view<ComTransform, ComPlayerInput>();
		for (auto entity : view) {
			auto& transform = view.get<ComTransform>(entity);
			auto input = view.get<ComPlayerInput>(entity);
			
			transform.position.x += 10.f;
		}
	}

}