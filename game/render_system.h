#pragma once

#include "core.h"
#include "system.h"
#include "game_fwd.h"

namespace terra
{
	class RenderSystem : public BaseSystem
	{
	public:
		RenderSystem(EntityAdmin* admin);
		~RenderSystem();

		void Render();
		void RenderComponents();
	private:
		void RenderSprite(SpriteComponent* sprite_component, SceneComponent* scene_component);
	};
}