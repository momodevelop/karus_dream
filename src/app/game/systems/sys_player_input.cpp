#include <constants.h>
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
			auto& anime = view.get<ComAnimation>(entity);
						

			using namespace character;
			if (sharedKeyboard.isKeyPressed(SharedKeyboard::UP)) {
				velocity.y += -1.f;
				auto animationIndex = animation::kIndicesSet[animation::BACK];
				anime.indices.clear();
				anime.indices.assign(
					animationIndex.cbegin(),
					animationIndex.cend()
				);
			}

			if (sharedKeyboard.isKeyPressed(SharedKeyboard::DOWN) {
				velocity.y += 1.f;
				anime.indices.clear();
			}
			if (sharedKeyboard.isKeyPressed(SharedKeyboard::LEFT) {
				velocity.x += -1.f;
				anime.indices.clear();
			}
			if (sharedKeyboard.isKeyPressed(SharedKeyboard::RIGHT) {
				velocity.x += 1.f;
				anime.indices.clear();
			}



			auto normVelocity = normalize(velocity);
			if (normVelocity.has_value())
				transform.position += normVelocity.value() * SPEED * dt;
		}
	}

}