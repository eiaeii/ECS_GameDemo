#pragma once

#include "core.h"
#include "ecs_fwd.h"

namespace terra
{
	class BaseSystem
	{
	protected: 
		EntityAdmin* admin_{ nullptr };
	public:
		BaseSystem(EntityAdmin* admin);
		virtual ~BaseSystem() = default;

		virtual bool Init() { return true; }
		virtual void Update(float time_step) {}
		virtual void Exit() {}
	};
}