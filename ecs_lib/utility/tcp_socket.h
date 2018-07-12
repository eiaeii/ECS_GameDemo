#pragma once

#include "core.h"
#include "socket_address.h"

namespace terra
{
	class TCPSocket
	{
	private:
		SOCKET		mSocket;
	public:
		TCPSocket(SOCKET inSocket) : mSocket(inSocket) {}
		~TCPSocket();
		int								Connect(const SocketAddress& inAddress);
		int								Bind(const SocketAddress& inToAddress);
		int								Listen(int inBackLog = 32);
		std::shared_ptr<TCPSocket>		Accept(SocketAddress& inFromAddress);
		int32_t							Send(const void* inData, size_t inLen);
		int32_t							Receive(void* inBuffer, size_t inLen);
		int								SetNonBlockingMode(bool inShouldBeNonBlocking);
	private:
		friend class SocketUtil;
	};

	using TCPSocketPtr = std::shared_ptr<TCPSocket>;
}