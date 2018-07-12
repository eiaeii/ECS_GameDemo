#include "server.h"

int main(int argc, char* argv[])
{
	using namespace terra;
	//using namespace std::chrono;
	//using namespace std::literals;
	__argc = argc;
	__argv = argv;


	if (Server::StaticInit())
	{
		return Server::sInstance->Run();
	}
	else
	{
		return 1;
	}

	return 0;
}