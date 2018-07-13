#pragma once

#include "entity.h"

namespace terra
{
	class TcpListener : public Entity
	{
	private:

	public:
		using Entity::Entity;

		virtual void InitializeComponents() override;
	};
}