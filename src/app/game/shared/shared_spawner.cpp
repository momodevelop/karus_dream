#include <array>

#include "shared_spawner.h"
#include "../components/com_transform.h"
#include "../components/com_renderable.h"
#include "../components/com_box_collider.h"
#include "../components/com_animation.h"
#include "../components/com_collectible.h"
#include "../components/com_enemy.h"

#include <constants.h>



namespace app::game::shared {
	using namespace components;
	using namespace ryoji::math;
	using namespace shared;

	struct EnemyTypeInfo {
		TextureHandler texture;
		SharedAnimationIndices::Indices animationIndex;
		int hp;
		Vec2f size;
	};
	const static EnemyTypeInfo enemyTypings[] = {
		{ TextureHandler::GHOST_SPRITESHEET, SharedAnimationIndices::ENEMY_GHOST, 3, {gEnemySize, gEnemySize} }, // GHOST
		{ TextureHandler::SKELETON_SPRITESHEET, SharedAnimationIndices::ENEMY_SKELETON, 3, {gEnemySize, gEnemySize} }, // SKELETON
		{ TextureHandler::FROG_SPRITESHEET, SharedAnimationIndices::ENEMY_FROG, 3, {gEnemySize, gEnemySize} }, // FROG
		{ TextureHandler::BAT_SPRITESHEET, SharedAnimationIndices::ENEMY_BAT, 3, {gEnemySize, gEnemySize} }, // BAT
	};

	SharedSpawner::SharedSpawner(entt::registry& ecs, SharedAnimationIndices& animationIndices)
		: coinTimer(0.f), coinDuration(10.f), ecs(ecs), animationIndices(animationIndices)
	{

	}
	SharedSpawner::~SharedSpawner()
	{
	}
	void SharedSpawner::update(float dt)
	{
		coinTimer += dt;
		if (coinTimer > coinDuration) {
			spawnCoin();
			coinTimer = 0.f;
		}
	}

	void SharedSpawner::spawnEnemy(Vec2f pos, bool facingRight, EnemyType type)
	{
		auto entity = ecs.create();
		ecs.assign<ComTransform>(entity, pos, enemyTypings[type].size);

		
		auto& enemy = ecs.assign<ComEnemy>(entity);
		auto& boxCollider = ecs.assign<ComBoxCollider>(entity);
		boxCollider.box = { 0.f, 0.f, gEnemySize, gEnemySize };
		
		auto& renderable = ecs.assign<ComRenderable>(entity);
		enemy.hp = enemyTypings[type].hp;

		renderable.textureHandler = enemyTypings[type].texture;
		auto& animation = ecs.assign<ComAnimation>(entity);
		auto& indices = animationIndices[enemyTypings[type].animationIndex];
		animation.indices.assign(indices.cbegin(), indices.cend());
		animation.speed = character::gAnimeSpeed;
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

