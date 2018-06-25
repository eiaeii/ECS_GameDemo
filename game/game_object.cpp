#include "game_object.h"

using namespace terra;

void GameObject::InitializeComponents()
{
	Add<SceneComponent>();
	Add<SpriteComponent>();
}
