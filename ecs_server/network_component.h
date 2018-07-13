#pragma once

#include "core.h"
#include "component.h"
#include "tcp_socket.h"

namespace terra
{
	class NetworkComponent : public BaseComponent
	{
	private:
		TCPSocketPtr socket_;
	public:
		using BaseComponent::BaseComponent;

		TCPSocketPtr GetSocket() { return socket_; }
		void SetTcpSocketPtr(TCPSocketPtr& in_socket)
		{
			socket_ = in_socket;
		}

	};
}