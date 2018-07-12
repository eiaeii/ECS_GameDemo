#pragma once

#include "core.h"
#include "system.h"

namespace terra
{
	class ConnectionSystem : public BaseSystem
	{
	public:
		using BaseSystem::BaseSystem;

		virtual bool Init() override;
		virtual void Update(float time_step) override;
	};
}