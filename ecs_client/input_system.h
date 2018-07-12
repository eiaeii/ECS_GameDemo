#pragma once

#include "core.h"
#include <SDL_events.h>
#include "system.h"

namespace terra
{
	class InputSystem : public BaseSystem
	{
	public:
		InputSystem(EntityAdmin* admin);
		~InputSystem();

		void HandleEvent(SDL_Event* in_event);

		virtual void Update(float time_step) override;
	};
}