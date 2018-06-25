#pragma once

#include "core.h"
#include <SDL_events.h>
#include "system.h"
#include "game_fwd.h"

namespace terra
{
	class CharacterMovementSystem : public BaseSystem
	{
	public:
		using BaseSystem::BaseSystem;

		virtual void Update(float time_step) override;

	private:
		void SimulateMovement(float delta_time);
		void AdjustVelocityByThrust(float delta_time, SceneComponent* scene_component, CharacterMovementComponent* movement_component);
	};
}