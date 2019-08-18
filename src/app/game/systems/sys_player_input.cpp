
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
			velocity.y += sharedKeyboard.isKeyPressed(SharedKeyboard::UP) ? -1.f : 0.f;
			velocity.y += sharedKeyboard.isKeyPressed(SharedKeyboard::DOWN) ? 1.f : 0.f;
			velocity.x += sharedKeyboard.isKeyPressed(SharedKeyboard::LEFT) ? -1.f : 0.f;
			velocity.x += sharedKeyboard.isKeyPressed(SharedKeyboard::RIGHT) ? 1.f : 0.f;

			auto normVelocity = normalize(velocity);
			if (normVelocity.has_value())
				transform.position += normVelocity.value() * SPEED * dt;
		}
	}

}