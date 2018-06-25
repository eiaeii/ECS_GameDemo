#pragma once

#include "core.h"
#include "component.h"
#include "textue.h"
namespace terra
{
	class SpriteComponent : public BaseComponent
	{
	private:
		Vector3 origin_;
		TexturePtr texture_;
	public:
		void Reset()
		{
		}
		Vector3 GetOrigin() const { return origin_; }
		void SetOrigin(const Vector3& origin)
		{
			origin_ = origin;
		}
		TexturePtr GetTexture() { return texture_; }
		void SetTexture(TexturePtr& texture) { texture_ = texture; }
	};
}