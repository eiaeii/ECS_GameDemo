#pragma once

#include "core.h"
#include "component.h"

namespace terra
{
	class SceneComponent : public BaseComponent
	{
	private:
		Vector3 location_;
		Vector3 color_;
		float collision_radius_{ 0.f };
		float rotation_{ 0.f };
		float scale_{ 1.f };
	public:
		using BaseComponent::BaseComponent;

		Vector3 GetLocation() const { return location_; }
		void SetLocation(const Vector3& location)
		{
			location_ = location;
		}
		Vector3 GetColor() const { return color_; }
		void SetColor(const Vector3& color)
		{
			color_ = color;
		}
		float GetScale() const { return scale_; }
		float GetRotation() const { return rotation_; }
		void SetRotation(float rotation) { rotation_ = rotation; }

		Vector3 GetForwardVector() const
		{
			//should we cache this when you turn?
			return Vector3(sinf(rotation_), -cosf(rotation_), 0.f);
		}
	};
}