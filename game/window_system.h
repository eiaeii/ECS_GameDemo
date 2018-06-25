#pragma once

#include "core.h"
#include "system.h"
#include <SDL.h>

namespace terra
{
	class WindowSystem : public BaseSystem
	{
	public:
		using BaseSystem::BaseSystem; 
		~WindowSystem();

		virtual bool Init() override;
	};
}