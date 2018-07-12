#pragma once

#include "core.h"
#include <SDL.h>
#include <SDL_events.h>
#include "game_fwd.h"

namespace terra
{
	class Client
	{
	protected:
		std::unique_ptr<TriangleGame> game_instance_;
		bool should_keep_running_{ true };
	public:
		static bool StaticInit();
		static std::unique_ptr<Client> client_instance_;
		Client();
		~Client();

		int Run();

	private:
		int DoRunLoop();
	};
}