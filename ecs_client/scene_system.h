#pragma once

#include "core.h"
#include "system.h"
#include <SDL.h>

namespace terra
{
	class SceneSystem : public BaseSystem
	{
	public:
		using BaseSystem::BaseSystem;
		~SceneSystem();

		virtual bool Init() override;

	private:
		void SpawnRandomActor(int ActorCount);
	};
}