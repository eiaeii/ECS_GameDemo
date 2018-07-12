#pragma once

#include "core.h"

namespace terra
{
	class SocketAddress
	{
	private:
		//friend class UDPSocket;
		friend class TCPSocket;

		sockaddr sock_addr_;
	public:
		SocketAddress(uint32_t in_address, uint16_t in_port)
		{
			GetAsSockAddrIn()->sin_family = AF_INET;
			GetIP4Ref() = htonl(in_address);
			GetAsSockAddrIn()->sin_port = htons(in_port);
		}

		SocketAddress(const sockaddr& in_sockaddr)
		{
			memcpy(&sock_addr_, &in_sockaddr, sizeof(sockaddr));
		}

		SocketAddress()
		{
			GetAsSockAddrIn()->sin_family = AF_INET;
			GetIP4Ref() = INADDR_ANY;
			GetAsSockAddrIn()->sin_port = 0;
		}

		bool operator==(const SocketAddress& in_other) const
		{
			return (sock_addr_.sa_family == AF_INET &&
				GetAsSockAddrIn()->sin_port == in_other.GetAsSockAddrIn()->sin_port) &&
				(GetIP4Ref() == in_other.GetIP4Ref());
		}

		size_t GetHash() const
		{
			return (GetIP4Ref()) |
				((static_cast<uint32_t>(GetAsSockAddrIn()->sin_port)) << 13) |
				sock_addr_.sa_family;
		}


		uint32_t				GetSize()			const { return sizeof(sockaddr); }

		//std::string					ToString()			const;
	private:
#if _WIN32
		uint32_t&				GetIP4Ref() { return *reinterpret_cast<uint32_t*>(&GetAsSockAddrIn()->sin_addr.S_un.S_addr); }
		const uint32_t&			GetIP4Ref()			const { return *reinterpret_cast<const uint32_t*>(&GetAsSockAddrIn()->sin_addr.S_un.S_addr); }
#else
		uint32_t&				GetIP4Ref() { return GetAsSockAddrIn()->sin_addr.s_addr; }
		const uint32_t&			GetIP4Ref()			const { return GetAsSockAddrIn()->sin_addr.s_addr; }
#endif

		sockaddr_in*			GetAsSockAddrIn() { return reinterpret_cast<sockaddr_in*>(&sock_addr_); }
		const	sockaddr_in*	GetAsSockAddrIn()	const { return reinterpret_cast<const sockaddr_in*>(&sock_addr_); }
	};
	using SocketAddressPtr = std::shared_ptr<SocketAddress>;
}

namespace std
{
	template<> struct hash<terra::SocketAddress>
	{
		size_t operator()(const terra::SocketAddress& socket_address) const
		{
			return socket_address.GetHash();
		}
	};
}