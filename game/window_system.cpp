#include "window_system.h"
#include "triangle_game.h"
#include "singleton_render.h"

using namespace terra;


WindowSystem::~WindowSystem()
{
	SDL_Window* main_window = static_cast<TriangleGame*>(admin_)->GetSingletonWindow()->main_window;
	if (main_window)
	{
		SDL_DestroyWindow(main_window);
	}
}

bool WindowSystem::Init()
{
	//1280,720
	SDL_Window* main_window = SDL_CreateWindow("ECS-Demo", 100, 100, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (main_window == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create window.");
		return false;
	}
	static_cast<TriangleGame*>(admin_)->GetSingletonWindow()->main_window = main_window;
	return true;
}
