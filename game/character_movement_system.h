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
		void AdjustRotationBySteer(SceneComponent* scene_component, CharacterMovementComponent* movement_component);
		void AdjustVelocityByThrust(SceneComponent* scene_component, CharacterMovementComponent* movement_component);
	};
}