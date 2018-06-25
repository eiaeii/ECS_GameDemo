#include "third_person_character.h"
#include "character_movement_component.h"
#include "player_input_component.h"

using namespace terra;

void ThirdPersonCharacter::InitializeComponents()
{
	Add<SceneComponent>();
	Add<SpriteComponent>();
	Add<CharacterMovementComponent>();
	Add<PlayerInputComponent>();
}
