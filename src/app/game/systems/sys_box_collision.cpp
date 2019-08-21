#include "sys_box_collision.h"
#include "../components/com_box_collider.h"
#include "../components/com_transform.h"

namespace app::game::systems {
	using namespace components;

	void SysCollider::update(entt::registry& registry)
	{
		auto view = registry.view<ComTransform, ComBoxCollider>();
		for (auto entity : view) {
			auto& transform = view.get<ComTransform>(entity);
			auto& box = view.get<ComBoxCollider>(entity);

			//if (box.collider.)
		}
	}
}