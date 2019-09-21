#include <array>
#include <random>

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
		uint8_t hp;
		Vec2f size;
	};
	const static EnemyTypeInfo enemyTypings[] = {
		{ TextureHandler::GHOST_SPRITESHEET, SharedAnimationIndices::ENEMY_GHOST, 3, {gEnemySize, gEnemySize} }, // GHOST
		{ TextureHandler::SKELETON_SPRITESHEET, SharedAnimationIndices::ENEMY_SKELETON, 3, {gEnemySize, gEnemySize} }, // SKELETON
		{ TextureHandler::FROG_SPRITESHEET, SharedAnimationIndices::ENEMY_FROG, 3, {gEnemySize, gEnemySize} }, // FROG
		{ TextureHandler::BAT_SPRITESHEET, SharedAnimationIndices::ENEMY_BAT, 3, {gEnemySize, gEnemySize} }, // BAT
	};

	struct LevelInfo {

	};


	SharedSpawner::SharedSpawner(entt::registry& ecs, SharedAnimationIndices& animationIndices)
		: coinTimer(0.f), coinDuration(10.f), ecs(ecs), 
		animationIndices(animationIndices),
		randomCoinGenerator(randomCoinDevice()),
		randomCoinX(gTileSize, gDisplayWidth - gHalfTileSize),
		randomCoinY(gTileSize, gDisplayHalfHeight - gHalfTileSize)
	{
	}
	SharedSpawner::~SharedSpawner()
	{
	}
	void SharedSpawner::update(float dt)
	{
		// coin spawn logic here
		coinTimer += dt;
		if (coinTimer > coinDuration) {
			int x = randomCoinX(randomCoinGenerator);
			int y = randomCoinY(randomCoinGenerator);
			spawnCoin(Vec2f{ float(x), float(y) });
			coinTimer = 0.f;
		}
	}

	void SharedSpawner::spawnEnemy(Vec2f pos, bool facingRight, EnemyType type)
	{
		auto entity = ecs.create();
		auto& transform = ecs.assign<ComTransform>(entity, 
			pos, 
			enemyTypings[type].size, 
			0.f, 
			facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL
		);

		auto& enemy = ecs.assign<ComEnemy>(entity,
			facingRight ? ComEnemy::STATE_MOVING_RIGHT : ComEnemy::STATE_MOVING_LEFT,
			enemyTypings[type].hp
		);
		auto& boxCollider = ecs.assign<ComBoxCollider>(entity,
			ryoji::aabb::AABB2f{ 0.f, 0.f, gEnemySize, gEnemySize }
		);
		
		auto& renderable = ecs.assign<ComRenderable>(entity);

		renderable.textureHandler = enemyTypings[type].texture;
		auto& animation = ecs.assign<ComAnimation>(entity);
		auto& indices = animationIndices[enemyTypings[type].animationIndex];
		animation.indices.assign(indices.cbegin(), indices.cend());
		animation.speed = character::gAnimeSpeed;
	}

	void SharedSpawner::spawnCoin(Vec2f pos)
	{
		auto entity = ecs.create();
		ecs.assign<ComTransform>(entity, pos, Vec2f{ float(gHalfTileSize), float(gHalfTileSize) });

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

