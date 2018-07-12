#pragma once

#include "core.h"
#include <SDL.h>
#include "textue.h"

namespace terra
{
	struct SingletonWindow
	{
		SDL_Window* main_window{ nullptr };
	};

	struct SingletonRenderer
	{
		SDL_Renderer* renderer{ nullptr };
		SDL_Rect GetLogicalViewport()
		{
			SDL_Rect view_port;
			SDL_RenderGetLogicalSize(renderer, &view_port.w, &view_port.h);
			return view_port;
		}
	};


	struct SingletonTexture
	{
	private:
		std::unordered_map<std::string, TexturePtr> name_to_texture_map_;

	public:
		TexturePtr GetTexture(const std::string& texture_name)
		{
			return name_to_texture_map_[texture_name];
		}
		void InsertTextue(const std::string& texture_name, TexturePtr& texture)
		{
			name_to_texture_map_[texture_name] = texture;
		}
		void InsertTextue(const std::string& texture_name, TexturePtr&& texture)
		{
			name_to_texture_map_[texture_name] = std::move(texture);
		}
	};

}