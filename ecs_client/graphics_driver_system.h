#pragma once
#include "core.h"
#include "system.h"
#include <SDL.h>

namespace terra
{
	class GraphicsDriverSystem : public BaseSystem
	{
	public:
		GraphicsDriverSystem(EntityAdmin* admin);
		~GraphicsDriverSystem();

		bool Init(SDL_Window* wnd);

		void Clear();
		void Present();
	};
}