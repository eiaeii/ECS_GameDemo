#include "graphics_driver_system.h"
#include "triangle_game.h"
#include "singleton_render.h"

using namespace terra;
GraphicsDriverSystem::GraphicsDriverSystem(EntityAdmin* admin)
	: BaseSystem(admin)
{
}

GraphicsDriverSystem::~GraphicsDriverSystem()
{
	SDL_Renderer* renderer = static_cast<TriangleGame*>(admin_)->GetSingletonRender()->renderer;
	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
	}
}


bool GraphicsDriverSystem::Init(SDL_Window* wnd)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create hardware-accelerated renderer.");
		return false;
	}
	// Cornflower blue background, cause why not?
	SDL_SetRenderDrawColor(renderer, 100, 149, 237, SDL_ALPHA_OPAQUE);
	// Set the logical size to 1280x720 so everything will just auto-scale
	SDL_RenderSetLogicalSize(renderer, 1280, 720);

	static_cast<TriangleGame*>(admin_)->GetSingletonRender()->renderer = renderer;
	return true;
}

void GraphicsDriverSystem::Clear()
{
	SDL_Renderer* renderer = static_cast<TriangleGame*>(admin_)->GetSingletonRender()->renderer;
	SDL_RenderClear(renderer);
}

void GraphicsDriverSystem::Present()
{
	SDL_Renderer* renderer = static_cast<TriangleGame*>(admin_)->GetSingletonRender()->renderer;
	SDL_RenderPresent(renderer);
}
