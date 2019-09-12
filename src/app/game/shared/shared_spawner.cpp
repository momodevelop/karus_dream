#include "shared_spawner.h"
#include "../components/com_transform.h"
#include "../components/com_renderable.h"
#include "../components/com_box_collider.h"
#include "../components/com_animation.h"
#include "../components/com_collectible.h"


#include <constants.h>

namespace app::game::shared {
	using namespace components;
	using namespace ryoji::math;
	using namespace shared;

	SharedSpawner::SharedSpawner(entt::registry& ecs, SharedAnimationIndices& animationIndices)
		: coinTimer(0.f), coinDuration(5.f), ecs(ecs), animationIndices(animationIndices)
	{

	}
	SharedSpawner::~SharedSpawner()
	{
	}
	void SharedSpawner::update(float dt)
	{
		coinTimer += coinDuration * dt;
		if (coinTimer > coinDuration) {
			spawnCoin();
			coinTimer = 0.f;
		}
	}

	void SharedSpawner::spawnCoin()
	{
		auto entity = ecs.create();
		ecs.assign<ComTransform>(entity, Vec2f{ 10.f, gSpawnableHeight }, Vec2f{ float(gHalfTileSize), float(gHalfTileSize) });

		auto& renderable = ecs.assign<ComRenderable>(entity);
		renderable.textureHandler = TextureHandler::COIN_SPRITESHEET;


		ecs.assign<ComCollectible>(entity);
		ecs.assign<ComBoxCollider>(entity, ryoji::aabb::AABB2f{ 0.f, 0.f, float(gHalfTileSize), float(gHalfTileSize) });


		auto& animation = ecs.assign<ComAnimation>(entity);
		auto& indices = animationIndices[SharedAnimationIndices::COIN];
		animation.indices.assign(indices.cbegin(), indices.cend());
		animation.speed = character::gAnimeSpeed;
	}
}

