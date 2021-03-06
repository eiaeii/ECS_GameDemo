#pragma once

#include "core.h"
#include "component.h"

namespace terra
{
	class CharacterMovementComponent : public BaseComponent
	{
	private:
		Vector3 velocity_;
		float max_linear_speed_{ 0.f };
		float max_rotation_speed_{ 0.f };
		float last_move_time_stamp_{ 0.f };
		float thrust_dir_{ 0.f };
		float steer_dir_{ 0.f };
	public:
		using BaseComponent::BaseComponent;

		void Reset() override
		{
			max_linear_speed_ = 3.f;
			max_rotation_speed_ = 3.f;
		}
		Vector3 GetVelocity() const { return velocity_; }
		void SetVelocity(const Vector3& velocity)
		{
			velocity_ = velocity;
		}
		float GetThrustDir() const { return thrust_dir_; }
		void SetThrustDir(float thrust_dir) { thrust_dir_ = thrust_dir; }
		float GetSteerDir() const { return steer_dir_; }
		void SetSteerDir(float steer_dir) { steer_dir_ = steer_dir; }
		float GetMaxLinearSpeed() const { return max_linear_speed_; }
		float GetMaxRotationSpeed() const { return max_rotation_speed_; }
	};
}