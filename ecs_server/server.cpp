#include "server.h"
#include <chrono>
#include <thread>
#include "frame_timer.h"
#include "socket_util.h"
#include "connection_system.h"
using namespace terra;


std::unique_ptr<Server> Server::server_instance_;

bool Server::StaticInit()
{
	server_instance_ = std::make_unique<Server>();
	return true;
}

Server::Server()
{
	SocketUtil::StaticInit();

	connection_system_ = std::make_unique<ConnectionSystem>(this);
}

terra::Server::~Server()
{
	SocketUtil::CleanUp();
}

bool Server::Init()
{
	if (!connection_system_->Init())
	{
		return false;
	}

	return true;
}

int Server::Run()
{
	using namespace std::chrono;
	using namespace std::literals;

	if (!server_instance_->Init())
	{
		return -1;
	}

	while (should_keep_running_)
	{
		FrameTimer::GetInstance()->Tick();

		Update(FrameTimer::GetInstance()->GetFrameTimeS());

		auto consumed_time = FrameTimer::GetInstance()->GetFrameTotalMs() - FrameTimer::GetInstance()->GetFrameStartTimeMs();
		int sleep_time = consumed_time < 100 ? static_cast<int>(100 - consumed_time) : 1;
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
	}
	server_instance_->Exit();
	return 0;
}

void Server::Update(float time_step)
{
	connection_system_->Update(time_step);
}

void Server::Exit()
{
}
