#include "input_system.h"
#include "triangle_game.h"
#include "singleton_input.h"
using namespace terra;

InputSystem::InputSystem(EntityAdmin* admin) : BaseSystem(admin)
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::HandleEvent(SDL_Event* in_event)
{
	switch (in_event->type)
	{
	case SDL_KEYDOWN:
		static_cast<TriangleGame*>(admin_)->GetSingletonInput()->HandleInput(EIA_Pressed, in_event->key.keysym.sym);
		break;
	case SDL_KEYUP:
		static_cast<TriangleGame*>(admin_)->GetSingletonInput()->HandleInput(EIA_Released, in_event->key.keysym.sym);
		break;
	default:
		break;
	}
}
