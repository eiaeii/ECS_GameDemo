#include "texture_system.h"
#include <SDL_image.h>
#include "triangle_game.h"
#include "graphics_driver_system.h"
#include "singleton_render.h"

using namespace terra;

TextureSystem::~TextureSystem()
{
}

bool TextureSystem::Init()
{
	CacheTexture("cat", "./Assets/cat.png");
	CacheTexture("mouse", "./Assets/mouse.png");
	CacheTexture("yarn", "./Assets/yarn.png");
	CacheTexture("yarn", "./Assets/triangle.png");
	return true;
}

bool TextureSystem::CacheTexture(const std::string& name, const char* file_name)
{
	TriangleGame* admin = static_cast<TriangleGame*>(admin_);
	SDL_Texture* texture = IMG_LoadTexture(admin->GetSingletonRender()->renderer, file_name);

	if (texture == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load texture: %s", file_name);
		return false;
	}

	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

	// Set the blend mode up so we can apply our colors
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	admin->GetSingletonTexture()->InsertTextue(name, std::make_shared<Texture>(w, h, texture));

	return true;
}
