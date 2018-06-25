#pragma once

#include "core.h"
#include "system.h"
#include <SDL.h>

namespace terra
{
	class TextureSystem : public BaseSystem
	{
	public:
		using BaseSystem::BaseSystem;
		~TextureSystem();

		virtual bool Init() override;
	private:
		bool CacheTexture(const std::string& name, const char* file_name);
	};
}