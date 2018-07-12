#include "server.h"

int main(int argc, char* argv[])
{
	using namespace terra;
	__argc = argc;
	__argv = argv;


	if (Server::StaticInit())
	{
		return Server::server_instance_->Run();
	}
	else
	{
		return 1;
	}

	return 0;
}