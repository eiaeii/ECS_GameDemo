#include "client.h"
#include "triangle_game.h"
#include "frame_timer.h"
#include "input_system.h"

using namespace terra;

std::unique_ptr<Client> Client::sInstance;

bool Client::StaticInit()
{
	sInstance = std::make_unique<Client>();
	return true;
}

Client::Client()
{
	game_instance_ = std::make_unique<TriangleGame>();

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
}


Client::~Client()
{
	SDL_Quit();
}

int Client::Run()
{
	return DoRunLoop();
}

int Client::DoRunLoop()
{
	bool quit = false;
	SDL_Event event;
	memset(&event, 0, sizeof(SDL_Event));

	if (!game_instance_->Init())
	{
		return -1;
	}

	while (!quit && should_keep_running_)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			else
			{
				game_instance_->GetInputSystem()->HandleEvent(&event);
			}
		}
		else
		{
			FrameTimer::GetInstance()->Tick();

			game_instance_->Update(FrameTimer::GetInstance()->GetFrameTimeS());
		}
	}
	game_instance_->Exit();
	return event.type;
}
