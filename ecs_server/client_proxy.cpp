#include "client_proxy.h"
#include "network_component.h"
using namespace terra;

void ClientProxy::InitializeComponents()
{
	Add<NetworkComponent>();
}
