#include "player_command_system.h"
#include "ecs_iterator.h"
#include "player_input_component.h"
#include "character_movement_component.h"
#include "scene_component.h"
#include "triangle_game.h"
#include "singleton_input.h"
#include "frame_timer.h"
using namespace terra;

void PlayerCommandSystem::Update(float time_step)
{
	ProcessInputState(time_step);
}

void PlayerCommandSystem::ProcessInputState(float delta_time)
{
	TriangleGame* admin = static_cast<TriangleGame*>(admin_);
	SingletonInput* singleton_input = admin->GetSingletonInput();
	for (PlayerInputComponent* player_input_component  : ComponentItr<PlayerInputComponent>(admin_))
	{
		CharacterMovementComponent* movement_component = player_input_component->Sibling<CharacterMovementComponent>();
		SceneComponent* scene_component = player_input_component->Sibling<SceneComponent>();
		if (movement_component && scene_component)
		{
			float forward_delta , back_delta, left_delta, right_delta;
			if (singleton_input->IsKeyDown('w'))
			{
				forward_delta = 1.f;
			}
			else
			{
				forward_delta = 0;
			}
			if (singleton_input->IsKeyDown('s'))
			{
				back_delta = 1.f;
			}
			else
			{
				back_delta = 0.f;
			}
			if (singleton_input->IsKeyDown('a'))
			{
				left_delta = 1.f;
			}
			else
			{
				left_delta = 0;
			}
			if (singleton_input->IsKeyDown('d'))
			{
				right_delta = 1.f;
			}
			else
			{
				right_delta = 0.f;
			}
			//float newRotation = scene_component->GetRotation() + input_state.GetDesiredHorizontalDelta()
			//	* movement_component->GetMaxRotationSpeed() * 0.03f;
			//scene_component->SetRotation(newRotation);
			//float forward_delta = input_state.GetDesiredVerticalDelta();
			movement_component->SetThrustDir(forward_delta - back_delta);
			movement_component->SetSteerDir(right_delta - left_delta);
		}
	
	}
}
