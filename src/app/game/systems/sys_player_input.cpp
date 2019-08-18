
#include <ryoji/vector.h>
#include "../components/com_transform.h"
#include "../components/com_player_input.h"
#include "../components/com_animation.h"
#include "sys_player_input.h"

#define SPEED 500.f

namespace app::game::systems {
	using namespace components;
	using namespace shared;
	using namespace ryoji::math;

	void SysPlayerInput::update(entt::registry& registry, SharedKeyboard& sharedKeyboard, float dt) {
		

		auto view = registry.view<ComTransform, ComPlayerInput, ComAnimation>();
		for (auto entity : view) {
			Vec2f velocity { 0.f, 0.f };

			auto& transform = view.get<ComTransform>(entity);
			if (sharedKeyboard.isKeyPressed(SharedKeyboard::UP)) {
				velocity.y = 1.f;
			}
			if (sharedKeyboard.isKeyPressed(SharedKeyboard::DOWN)) {
				velocity.y = -1.f;
			}
			if (sharedKeyboard.isKeyPressed(SharedKeyboard::LEFT)) {
				velocity.x = -1.f;
			}
			if (sharedKeyboard.isKeyPressed(SharedKeyboard::RIGHT)) {
				velocity.x = 1.f;
			}
			//velocity = normalize(velocity);
		

			//transform.position += velocity * SPEED * dt;
			//transform.position += Vec2f{ 0.f, 0.f };
		}
	}

}