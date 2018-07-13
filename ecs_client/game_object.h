#pragma once

#include "entity.h"
#include "game_fwd.h"
#include "scene_component.h"
#include "sprite_component.h"

namespace terra
{
	class GameObject : public Entity
	{
	private:

	public:
		using Entity::Entity;

		virtual void InitializeComponents() override;

		SceneComponent* GetSceneComponent() { return Get<SceneComponent>(); }
	};
}