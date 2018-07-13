#pragma once

#include "entity.h"

namespace terra
{
	class ClientProxy : public Entity
	{
	private:

	public:
		using Entity::Entity;

		virtual void InitializeComponents() override;
	};
}