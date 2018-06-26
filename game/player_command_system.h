#pragma once

#include "core.h"
#include <SDL_events.h>
#include "system.h"

namespace terra
{
	class PlayerCommandSystem : public BaseSystem
	{
	public:
		using BaseSystem::BaseSystem;

		virtual void Update(float time_step) override;

	private:
		void ProcessInputState(float delta_time);
		bool IsTimeToSampleInput();
	};
}