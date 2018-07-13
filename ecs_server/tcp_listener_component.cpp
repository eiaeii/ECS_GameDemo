#include "tcp_listener_component.h"
#include "socket_util.h"

using namespace terra;

bool TcpListenerComponent::Listen(uint16_t port)
{
	socket_ = SocketUtil::CreateTCPSocket(SocketAddressFamily::INET);
	if (!socket_)
	{
		return false;
	}
	SocketAddress socket_address(INADDR_ANY, port);
	socket_->Bind(socket_address);
	socket_->Listen();
	return true;
}
