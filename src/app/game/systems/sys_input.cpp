#include "../components/com_transform.h"
#include "sys_input.h"

namespace app::game::systems {
	using namespace components;
	void SysInput::handleEvent(entt::registry& registry, SDL_Event& e) {
		auto view = registry.view<ComTransform>();
		for (auto entity : view) {
			//auto& transform = view.get<ComTransform>(entity);

			
		}
	}

}