#ifndef __APP_GAME_SYSTEMS_ANIMATION_H__
#define __APP_GAME_SYSTEMS_ANIMATION_H__


namespace app::game::systems {

	class SysAnimation {
	public:
		static void updateCharacterAnimationType(entt::registry& registry, shared::SharedCharacterAnimations& characterAnimations);
		static void updateAnimation(entt::registry& registry, shared::SharedTextures& sharedTextures, float dt);
	};
}


#endif