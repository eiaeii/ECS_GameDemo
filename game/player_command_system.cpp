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
	if (!IsTimeToSampleInput())
	{
		return;
	}
	TriangleGame* admin = static_cast<TriangleGame*>(admin_);
	SingletonInput* singleton_input = admin->GetSingletonInput();
	const InputState& input_state = singleton_input->current_state;
	for (PlayerInputComponent* player_input_component  : ComponentItr<PlayerInputComponent>(admin_))
	{
		CharacterMovementComponent* movement_component = player_input_component->Sibling<CharacterMovementComponent>();
		SceneComponent* scene_component = player_input_component->Sibling<SceneComponent>();
		if (movement_component && scene_component)
		{
			float newRotation = scene_component->GetRotation() + input_state.GetDesiredHorizontalDelta()
				* movement_component->GetMaxRotationSpeed() * delta_time;
			scene_component->SetRotation(newRotation);
			float forward_delta = input_state.GetDesiredVerticalDelta();
			movement_component->SetThrustDir(forward_delta);
		}
	
	}
}

bool PlayerCommandSystem::IsTimeToSampleInput()
{
	static float mNextTimeToSampleInput = 0.f;
	static const float kTimeBetweenInputSamples = 0.03f;
	float time = FrameTimer::GetInstance()->GetFrameTotalS();
	if (time > mNextTimeToSampleInput)
	{
		mNextTimeToSampleInput = mNextTimeToSampleInput + kTimeBetweenInputSamples;
		return true;
	}

	return false;
}
