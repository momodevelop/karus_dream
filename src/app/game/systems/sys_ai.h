#ifndef __APP_GAME_SYSTEMS_AI_H__
#define __APP_GAME_SYSTEMS_AI_H__


namespace app::game::systems {

	class SysAi {
	public:
		static void updateEnemyAi(entt::registry& ecs, float dt);
	};
}


#endif