#pragma once

#include "game_object.h"
#include "game_fwd.h"

namespace terra
{
	class ThirdPersonCharacter : public GameObject
	{
	private:

	public:
		using GameObject::GameObject;

		virtual void InitializeComponents() override;
	};
}