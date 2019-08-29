#include <entt.h>


#include "../components/com_transform.h"
#include "../components/com_rigidbody.h"
#include "../components/com_constant_force.h"

#include "sys_physics.h"


namespace app::game::systems {
	using namespace components;
	void SysPhysics::updateConstantForces(entt::registry& ecs) {
		auto view = ecs.view<ComConstantForce, ComRigidBody>();
		for (auto entity : view) {
			auto& force = view.get<ComConstantForce>(entity);
			auto& rigidbody = view.get<ComRigidBody>(entity);

			rigidbody.acceleration = force.force;
		}
	}

	void SysPhysics::updateMovement(entt::registry& ecs, float dt)
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