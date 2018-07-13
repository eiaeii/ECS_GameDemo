#pragma once

#include "core.h"
#include "component.h"
#include "tcp_socket.h"

namespace terra
{
	class TcpListenerComponent : public BaseComponent
	{
	private:
		TCPSocketPtr socket_;
	public:
		using BaseComponent::BaseComponent;

		bool Listen(uint16_t port);
		TCPSocketPtr GetSocket() { return socket_; }
	};
}