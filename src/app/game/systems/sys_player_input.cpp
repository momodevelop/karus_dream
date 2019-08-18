
#include <ryoji/vector.h>
#include "../components/com_transform.h"
#include "../components/com_player_input.h"
#include "../components/com_animation.h"
#include "sys_player_input.h"

#define SPEED 500.f * dt;

namespace app::game::systems {
	using namespace components;
	using namespace shared;
	using namespace ryoji::math;

	void SysPlayerInput::update(entt::registry& registry, SharedKeyboard& sharedKeyboard, float dt) {
		

		auto view = registry.view<ComTransform, ComPlayerInput, ComAnimation>();
		for (auto entity : view) {
			

			auto& transform = view.get<ComTransform>(entity);
			if (sharedKeyboard.isKeyPressed(SharedKeyboard::UP)) {
				transform.position.y -= SPEED;
			}
			else if (sharedKeyboard.isKeyPressed(SharedKeyboard::DOWN)) {
				transform.position.y += SPEED;
			}

			else if (sharedKeyboard.isKeyPressed(SharedKeyboard::LEFT)) {
				transform.position.x -= SPEED;
			}

			else if (sharedKeyboard.isKeyPressed(SharedKeyboard::RIGHT)) {
				transform.position.x += SPEED;
			}

			
			
		}
	}

}