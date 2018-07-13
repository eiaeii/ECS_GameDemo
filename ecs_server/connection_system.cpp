#include "connection_system.h"
#include "tcp_listener.h"
#include "tcp_listener_component.h"
#include "string_utils.h"
#include "socket_util.h"
#include "ecs_iterator.h"
#include "client_proxy.h"
#include "network_component.h"
using namespace terra;

bool ConnectionSystem::Init()
{
	std::string portString = StringUtils::GetCommandLineArg(1);
	uint16_t port = stoi(portString);
	TcpListener* tcp_listener = admin_->SpawnEntity<TcpListener>();
	tcp_listener->InitializeComponents();
	TcpListenerComponent* comp = tcp_listener->Get<TcpListenerComponent>();
	comp->Listen(port);
	LOG("Port %d Start Listening", port);
	return true;
}

void ConnectionSystem::Update(float time_step)
{
	HandleNewConnection();
	ProcessIncomingPackets();
}

void ConnectionSystem::HandleNewConnection()
{
	std::vector<TCPSocketPtr> listen_sockets;
	for (TcpListenerComponent* c : ComponentItr<TcpListenerComponent>(
		admin_, [](TcpListenerComponent* c) { return c->GetSocket() != nullptr; }))
	{
		listen_sockets.push_back(c->GetSocket());
	}
	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	std::vector<TCPSocketPtr> new_sockets;
	//to see whether there are some new connections
	int ret = SocketUtil::Select(&listen_sockets, &new_sockets, nullptr, nullptr, nullptr, nullptr, &tv);
	if (ret < 0)
	{
		//error!
	}
	for (auto& e : new_sockets)
	{
		SocketAddress address;
		TCPSocketPtr new_socket = e->Accept(address);
	 	ClientProxy* client_proxy = admin_->SpawnEntity<ClientProxy>();
		client_proxy->InitializeComponents();
		NetworkComponent* network_component = client_proxy->Get<NetworkComponent>();
		network_component->SetTcpSocketPtr(new_socket);
	}
}

void ConnectionSystem::HandleDisconnection()
{
}

void terra::ConnectionSystem::ProcessIncomingPackets()
{
	std::vector<TCPSocketPtr> client_sockets;
	for (NetworkComponent* c : ComponentItr<NetworkComponent>(
		admin_, [](NetworkComponent* c) { return c->GetSocket() != nullptr; }))
	{
		client_sockets.push_back(c->GetSocket());
	}

	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	std::vector<TCPSocketPtr> rd_sockets;
	int ret = SocketUtil::Select(&client_sockets, &rd_sockets, nullptr, nullptr, nullptr, nullptr, &tv);
	if (ret < 0)
	{
		//error!
	}
	for (auto& e : rd_sockets)
	{
	}
}
