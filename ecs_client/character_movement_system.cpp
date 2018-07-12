#include "character_movement_system.h"
#include "character_movement_component.h"
#include "scene_component.h"
#include "ecs_iterator.h"
using namespace terra;

void CharacterMovementSystem::Update(float time_step)
{
	SimulateMovement(time_step);
}

void CharacterMovementSystem::SimulateMovement(float delta_time)
{
	for (std::tuple<SceneComponent*, CharacterMovementComponent*>&& tup : ComponentItr<SceneComponent, CharacterMovementComponent>(admin_))
	{
		SceneComponent* scene_component = std::get<0>(tup);
		CharacterMovementComponent* movement_component = std::get<1>(tup);

		float newRotation = scene_component->GetRotation() + movement_component->GetSteerDir()
			* movement_component->GetMaxRotationSpeed() * delta_time;
		scene_component->SetRotation(newRotation);

		AdjustVelocityByThrust(scene_component, movement_component);
		Vector3 old_location = scene_component->GetLocation();
		Vector3 current_velocity = movement_component->GetVelocity();
		scene_component->SetLocation(old_location + current_velocity * delta_time);
	}
}

void CharacterMovementSystem::AdjustRotationBySteer(SceneComponent * scene_component, CharacterMovementComponent * movement_component)
{
}

void CharacterMovementSystem::AdjustVelocityByThrust(SceneComponent* scene_component, CharacterMovementComponent* movement_component)
{
	//just set the velocity based on the thrust direction -- no thrust will lead to 0 velocity
	//simulating acceleration makes the client prediction a bit more complex
	Vector3 forward_vector = scene_component->GetForwardVector();
	float thrust_dir = movement_component->GetThrustDir();
	float max_linear_speed = movement_component->GetMaxLinearSpeed();
	movement_component->SetVelocity(forward_vector * (thrust_dir * max_linear_speed));
}
