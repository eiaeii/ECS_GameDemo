#include "connection_system.h"
#include "string_utils.h"
#include "socket_util.h"
using namespace terra;

bool ConnectionSystem::Init()
{
	std::string portString = StringUtils::GetCommandLineArg(1);
	uint16_t port = stoi(portString);
	TCPSocketPtr tcp_socket_ = SocketUtil::CreateTCPSocket(SocketAddressFamily::INET);
	if (!tcp_socket_)
	{
		return false;
	}
	SocketAddress listen_address(INADDR_ANY, port);
	tcp_socket_->Bind(listen_address);
	tcp_socket_->Listen();
	return true;
}

void ConnectionSystem::Update(float time_step)
{

}
