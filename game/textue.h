#pragma once

#include "core.h"
#include <SDL.h>

namespace terra
{
	class Texture
	{
	private:
		uint32_t width_{ 0 };
		uint32_t height_{ 0 };
		SDL_Texture* texture_{ nullptr };
	public:
		Texture(uint32_t width, uint32_t height, SDL_Texture* texture)
			: width_(width), height_(height), texture_(texture)
		{
		}
		uint32_t	GetWidth()	const { return width_; }
		uint32_t	GetHeight()	const { return height_; }
		SDL_Texture* GetData() const { return texture_; }
	};
	using TexturePtr = std::shared_ptr<Texture>;
}