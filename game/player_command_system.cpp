#include "player_command_system.h"

using namespace terra;

void PlayerCommandSystem::Update(float time_step)
{
	ProcessInputState(time_step);
}

void PlayerCommandSystem::ProcessInputState(float delta_time)
{
	//for (std::tuple<SceneComponent*, CharacterMovementComponent*, >&& tup : ComponentItr<SceneComponent, CharacterMovementComponent>(admin_))
	//{
	//	SceneComponent* scene_component = std::get<0>(tup);
	//	CharacterMovementComponent* movement_component = std::get<1>(tup);
	//	AdjustVelocityByThrust(delta_time, scene_component, movement_component);
	//	Vector3 old_location = scene_component->GetLocation();
	//	Vector3 current_velocity = movement_component->GetVelocity();
	//	scene_component->SetLocation(old_location + current_velocity * delta_time);
	//}
}
