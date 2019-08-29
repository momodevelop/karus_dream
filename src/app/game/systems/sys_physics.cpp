#include "sys_physics.h"

#include "../components/com_transform.h"
#include "../components/com_rigidbody.h"

namespace app::game::systems {
	using namespace components;
	void SysPhysics::update(entt::registry& ecs, float dt)
	{
		auto view = ecs.view<ComTransform, ComRigidBody>();
		for (auto entity : view) {
			auto& transform = view.get<ComTransform>(entity);
			auto& rigidbody = view.get<ComRigidBody>(entity);

			rigidbody.velocity += rigidbody.acceleration * dt;
			transform.position += rigidbody.velocity * dt;

		}
	}
}